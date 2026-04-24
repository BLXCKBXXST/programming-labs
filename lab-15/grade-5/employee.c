#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "employee.h"

int load_csv(const char *filename, Employee *employees, int max) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        fprintf(stderr, "Ошибка: не удалось открыть файл '%s'\n", filename);
        return -1;
    }

    int count = 0;
    char line[256];

    while (count < max && fgets(line, sizeof(line), f)) {
        line[strcspn(line, "\r\n")] = '\0';
        if (line[0] == '\0') continue;

        char *name  = strtok(line, ";");
        char *id_s  = strtok(NULL, ";");
        char *level = strtok(NULL, ";");

        if (!name || !id_s || !level) continue;

        strncpy(employees[count].name,  name,  MAX_NAME  - 1);
        strncpy(employees[count].level, level, MAX_LEVEL - 1);
        employees[count].name[MAX_NAME   - 1] = '\0';
        employees[count].level[MAX_LEVEL - 1] = '\0';
        employees[count].id = atoi(id_s);
        count++;
    }

    fclose(f);
    return count;
}

void print_table(const Employee *employees, int count) {
    printf("%-5s %-24s %-8s %-10s\n", "№", "Имя", "ID", "Уровень");
    printf("%-5s %-24s %-8s %-10s\n", "---", "------------------------", "--------", "----------");
    for (int i = 0; i < count; i++) {
        printf("%-5d %-24s %-8d %-10s\n",
               i + 1,
               employees[i].name,
               employees[i].id,
               employees[i].level);
    }
}

int save_database(const Employee *employees, int count) {
    FILE *f = fopen(DATABASE_FILE, "wb");
    if (!f) {
        fprintf(stderr, "Ошибка: не удалось создать '%s'\n", DATABASE_FILE);
        return -1;
    }

    if (fwrite(&count, sizeof(int), 1, f) != 1) {
        fprintf(stderr, "Ошибка записи количества записей\n");
        fclose(f);
        return -1;
    }

    if (fwrite(employees, sizeof(Employee), count, f) != (size_t)count) {
        fprintf(stderr, "Ошибка записи данных сотрудников\n");
        fclose(f);
        return -1;
    }

    fclose(f);
    return 0;
}

void search_by_id(void) {
    FILE *f = fopen(DATABASE_FILE, "rb");
    if (!f) {
        fprintf(stderr, "Ошибка: не удалось открыть '%s'\n", DATABASE_FILE);
        return;
    }

    int count = 0;
    if (fread(&count, sizeof(int), 1, f) != 1) {
        fprintf(stderr, "Ошибка чтения базы данных\n");
        fclose(f);
        return;
    }

    int search_id;
    printf("Введите ID сотрудника: ");
    if (scanf("%d", &search_id) != 1) {
        fprintf(stderr, "Ошибка ввода\n");
        fclose(f);
        return;
    }

    Employee emp;
    int found = 0;
    while (fread(&emp, sizeof(Employee), 1, f) == 1) {
        if (emp.id == search_id) {
            printf("\nНайден сотрудник:\n");
            printf("  Имя:     %s\n", emp.name);
            printf("  ID:      %d\n", emp.id);
            printf("  Уровень: %s\n", emp.level);
            found = 1;
            break;
        }
    }

    if (!found) {
        fprintf(stderr, "Ошибка: сотрудник с ID %d не найден\n", search_id);
    }

    fclose(f);
}

/* RLE: формат пары [count (1 байт)][value (1 байт)], count от 1 до 255 */
int compress(void) {
    FILE *in = fopen(DATABASE_FILE, "rb");
    if (!in) {
        fprintf(stderr, "Ошибка: не удалось открыть '%s'\n", DATABASE_FILE);
        return -1;
    }

    FILE *out = fopen(RLE_FILE, "wb");
    if (!out) {
        fprintf(stderr, "Ошибка: не удалось создать '%s'\n", RLE_FILE);
        fclose(in);
        return -1;
    }

    int cur = fgetc(in);
    while (cur != EOF) {
        unsigned char val   = (unsigned char)cur;
        unsigned char count = 1;
        int next;
        while (count < 255 && (next = fgetc(in)) != EOF && (unsigned char)next == val) {
            count++;
        }
        fputc(count, out);
        fputc(val,   out);

        if (count < 255) {
            cur = (next == EOF) ? EOF : next;
        } else {
            cur = fgetc(in);
        }
    }

    fclose(in);
    fclose(out);

    FILE *f1 = fopen(DATABASE_FILE, "rb");
    FILE *f2 = fopen(RLE_FILE,      "rb");
    if (!f1 || !f2) { if (f1) fclose(f1); if (f2) fclose(f2); return -1; }

    fseek(f1, 0, SEEK_END); long size_before = ftell(f1);
    fseek(f2, 0, SEEK_END); long size_after  = ftell(f2);
    fclose(f1); fclose(f2);

    double ratio = (size_before > 0)
                   ? (1.0 - (double)size_after / size_before) * 100.0
                   : 0.0;

    printf("Размер до: %.2f Кб, Размер после: %.2f Кб. Сжатие: %.1f%%\n",
           size_before / 1024.0, size_after / 1024.0, ratio);

    return 0;
}

int decompress(void) {
    FILE *in = fopen(RLE_FILE, "rb");
    if (!in) {
        fprintf(stderr, "Ошибка: не удалось открыть '%s'\n", RLE_FILE);
        return -1;
    }

    FILE *out = fopen("database_restored.dat", "wb");
    if (!out) {
        fprintf(stderr, "Ошибка: не удалось создать 'database_restored.dat'\n");
        fclose(in);
        return -1;
    }

    int c;
    while ((c = fgetc(in)) != EOF) {
        unsigned char count = (unsigned char)c;
        int val = fgetc(in);
        if (val == EOF) {
            fprintf(stderr, "Ошибка: повреждённый RLE-файл\n");
            fclose(in);
            fclose(out);
            return -1;
        }
        for (unsigned char i = 0; i < count; i++) {
            fputc(val, out);
        }
    }

    fclose(in);
    fclose(out);
    printf("Файл восстановлен: 'database_restored.dat'\n");
    return 0;
}
