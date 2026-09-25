/*
 * task_star — симулятор 4G/5G сети. Найденные и исправленные баги:
 *
 *  1. register_device: цикл i <= 5 пишет в connected_cells[5] за границу
 *     массива размера 5 → stack-buffer-overflow.
 *
 *  2. calculate_signal_strength: при distance ≤ 0 log10 даёт −∞/NaN,
 *     а ветка `if (distance < 0.1)` уходит в бесконечную рекурсию
 *     при distance == 0. Плюс переменная `normalized` использовалась
 *     до инициализации (UB).
 *
 *  3. calculate_network_metrics: проверка `device_id > device_count`
 *     должна быть `>=` (off-by-one). Плюс packet_loss не инициализирован.
 *
 *  4. handover_device: те же off-by-one в `device_index > device_count`
 *     и `i <= tower_count`.
 *
 *  5. aggregate_traffic: деление на device_count без проверки на 0.
 *
 *  6. get_cell_status: возвращался указатель на локальный массив
 *     `char status[50]` → use-after-return. Перешли на static buffer.
 *
 *  7. measure_qos: `int mask = 1 << 31` — UB при signed-сдвиге за знак.
 *     Сменили на unsigned 1u << 31. Бесполезный `bitrate >> 31` удалён.
 *
 *  8. balance_load: цикл шёл по sizeof(towers)/sizeof(towers[0]) = 50,
 *     перебирая неинициализированные башни. Плюс `i++` внутри тела
 *     цикла удваивал инкремент. Перешли на простой `for (i; i<tower_count; i++)`.
 *
 *  9. add_network_slice: realloc(slices, slice_count + 1) без умножения
 *     на sizeof(char*) — выделялось в 8 раз меньше памяти, чем нужно.
 *
 * 10. В main:
 *      - device_ptr использовался без инициализации (UB),
 *      - double free на buffer,
 *      - strcpy в char small_buffer[10] длинной строки → stack overflow.
 *     Эти три блока удалены, так как они не несут полезной нагрузки.
 *
 * Найдено: AddressSanitizer (по большинству багов сразу указывает строку)
 * и UndefinedBehaviorSanitizer (для int shift / неинициализированных).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define MAX_DEVICES 100
#define MAX_TOWERS 50

typedef struct {
    char device_id[20];
    float signal_strength;
    int connected_cells[5];
    float throughput_mbps;
    char technology[5];
} MobileDevice;

typedef struct {
    int cell_id;
    float frequency_ghz;
    float max_bandwidth;
    int active_users;
    float load_percentage;
    char cell_type[10];
} CellTower;

typedef struct {
    float dl_speed;
    float ul_speed;
    int latency_ms;
    int packet_loss;
} NetworkMetrics;

MobileDevice devices[MAX_DEVICES];
CellTower towers[MAX_TOWERS];
int device_count = 0;
int tower_count = 0;

void register_device(const char *device_id, const char *technology) {
    if (device_count >= MAX_DEVICES) {
        printf("Maximum devices reached!\n");
        return;
    }

    strncpy(devices[device_count].device_id, device_id,
            sizeof devices[device_count].device_id - 1);
    devices[device_count].device_id[sizeof devices[device_count].device_id - 1] = '\0';

    strncpy(devices[device_count].technology, technology,
            sizeof devices[device_count].technology - 1);
    devices[device_count].technology[sizeof devices[device_count].technology - 1] = '\0';

    devices[device_count].signal_strength = 0;
    devices[device_count].throughput_mbps = 0;

    for (int i = 0; i < 5; i++) {                    /* было: i <= 5 */
        devices[device_count].connected_cells[i] = -1;
    }

    device_count++;
}

void add_cell_tower(int cell_id, float frequency, float bandwidth, const char *type) {
    if (tower_count >= MAX_TOWERS) return;

    towers[tower_count].cell_id = cell_id;
    towers[tower_count].frequency_ghz = frequency;
    towers[tower_count].max_bandwidth = bandwidth;
    towers[tower_count].active_users = 0;
    strncpy(towers[tower_count].cell_type, type, sizeof towers[tower_count].cell_type - 1);
    towers[tower_count].cell_type[sizeof towers[tower_count].cell_type - 1] = '\0';
    towers[tower_count].load_percentage = 0;

    tower_count++;
}

float calculate_signal_strength(float distance_km, float frequency_ghz) {
    if (distance_km < 0.01f) distance_km = 0.01f;    /* было: рекурсия + log10(0) */

    float loss = 20 * log10(distance_km) + 20 * log10(frequency_ghz) + 32.44f;
    float signal = 100 - loss;
    float normalized = 0;                            /* было: использовалась без init */
    if (signal > 0) normalized = signal / 100;

    return normalized * 100;
}

void calculate_network_metrics(NetworkMetrics *metrics, int device_id) {
    metrics->packet_loss = 0;                        /* было: не инициализировалось */

    if (device_id < 0 || device_id >= device_count) { /* было: > device_count */
        metrics->dl_speed = 0;
        metrics->ul_speed = 0;
        metrics->latency_ms = 0;
        return;
    }

    MobileDevice *device = &devices[device_id];

    if (strcmp(device->technology, "5G") == 0) {
        metrics->dl_speed = device->signal_strength * 10;
        metrics->ul_speed = metrics->dl_speed / 4;
        metrics->latency_ms = (int)(20 - device->signal_strength / 10);
    } else if (strcmp(device->technology, "4G") == 0) {
        metrics->dl_speed = device->signal_strength * 2;
        metrics->ul_speed = metrics->dl_speed / 5;
        metrics->latency_ms = (int)(50 - device->signal_strength / 5);
    } else {
        metrics->dl_speed = 0;
        metrics->ul_speed = 0;
        metrics->latency_ms = 0;
    }

    if (metrics->latency_ms < 0) metrics->latency_ms = -metrics->latency_ms;
}

void handover_device(int device_index, int from_cell, int to_cell) {
    if (device_index < 0 || device_index >= device_count) return;  /* было: > device_count */

    MobileDevice *device = &devices[device_index];

    int from_index = -1, to_index = -1;
    for (int i = 0; i < tower_count; i++) {           /* было: i <= tower_count */
        if (towers[i].cell_id == from_cell) from_index = i;
        if (towers[i].cell_id == to_cell)   to_index = i;
    }

    if (from_index != -1) towers[from_index].active_users--;
    if (to_index   != -1) towers[to_index].active_users++;

    for (int i = 0; i < 5; i++) {
        if (device->connected_cells[i] == from_cell) {
            device->connected_cells[i] = to_cell;
            break;
        }
    }
}

void aggregate_traffic(int cell_id) {
    float total_throughput = 0;                       /* было: int — потеря точности */
    int users = 0;

    for (int i = 0; i < device_count; i++) {
        for (int j = 0; j < 5; j++) {
            if (devices[i].connected_cells[j] == cell_id) {
                total_throughput += devices[i].throughput_mbps;
                users++;
                break;
            }
        }
    }

    float average = users > 0 ? total_throughput / users : 0;  /* было: /device_count, могло быть 0 */
    printf("Cell %d: %d users, average throughput: %.2f Mbps\n", cell_id, users, average);
}

const char *get_cell_status(int cell_id) {
    static char status[64];                           /* было: на стеке → use-after-return */
    snprintf(status, sizeof status, "Cell %d is active", cell_id);
    return status;
}

void measure_qos(const MobileDevice *device) {
    if (device->throughput_mbps > 100) {
        printf("Excellent quality for %s\n", device->device_id);
    }

    /* было: int mask = 1 << 31 (UB) и бесполезный bitrate >> 31 — удалены */
    unsigned int mask = 1u << 31;
    (void)mask;                                       /* демонстрация, не используется */
}

void balance_load(void) {
    for (int i = 0; i < tower_count; i++) {           /* было: sizeof(towers)/sizeof(towers[0]) */
        if (towers[i].load_percentage > 80) {
            towers[i].load_percentage -= 10;          /* было: i++ удваивал инкремент */
        }
    }
}

void add_network_slice(const char *slice_name) {
    static char **slices = NULL;
    static int slice_count = 0;

    /* было: realloc(slices, slice_count + 1) — забыли sizeof(char*) */
    char **new_slices = realloc(slices, (slice_count + 1) * sizeof(char *));
    if (!new_slices) return;
    slices = new_slices;

    slices[slice_count] = malloc(strlen(slice_name) + 1);
    if (!slices[slice_count]) return;
    strcpy(slices[slice_count], slice_name);
    slice_count++;
}

/* ============= ТЕСТЫ ============= */

void test_registration(void) {
    printf("\n=== Test Device Registration ===\n");
    register_device("iPhone12", "4G");
    register_device("GalaxyS21", "5G");
    register_device("Pixel6", "4G");
    printf("Registered %d devices\n", device_count);
}

void test_signal_calculation(void) {
    printf("\n=== Test Signal Calculation ===\n");
    float signal = calculate_signal_strength(0, 2.4f);
    printf("Signal at 0 km (clamped): %.2f\n", signal);
    signal = calculate_signal_strength(1, 3.5f);
    printf("Signal at 1 km (3.5 GHz): %.2f\n", signal);
}

void test_handover(void) {
    printf("\n=== Test Handover ===\n");
    add_cell_tower(101, 1.8f, 100, "macro");
    add_cell_tower(102, 3.5f, 400, "small");

    devices[0].connected_cells[0] = 101;
    handover_device(0, 101, 102);
    printf("Handover complete\n");
}

void test_qos_monitoring(void) {
    printf("\n=== Test QoS Monitoring ===\n");
    NetworkMetrics metrics;
    calculate_network_metrics(&metrics, 0);
    printf("DL Speed: %.2f Mbps\n", metrics.dl_speed);
    printf("Latency:  %d ms\n", metrics.latency_ms);
    printf("Packet Loss: %d\n", metrics.packet_loss);
}

int main(void) {
    printf("========================================\n");
    printf("4G/5G NETWORK SIMULATOR (fixed)\n");
    printf("========================================\n");

    test_registration();
    test_signal_calculation();
    test_handover();
    test_qos_monitoring();

    /* было: разыменование неинициализированного device_ptr — удалено */

    /* было: double free buffer — удалено */
    char *buffer = malloc(100);
    free(buffer);

    /* было: stack overflow при strcpy длинной строки в char[10] */
    char small_buffer[64];
    snprintf(small_buffer, sizeof small_buffer, "%s", "Short safe string");
    printf("Buffer: %s\n", small_buffer);

    return 0;
}
