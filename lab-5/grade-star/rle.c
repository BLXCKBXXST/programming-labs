#include <stdio.h>
#include <string.h>

// Бонус (*): Алгоритм сжатия RLE (Run-Length Encoding)
// Заменяет повторяющиеся последовательности на пары (значение, счётчик)

int rle_compress(int input[], int size, int compressed[]) {
    if (size == 0) return 0;
    int compressed_size = 0;
    int i = 0;
    while (i < size) {
        int value = input[i];
        int count = 1;
        while (i + count < size && input[i + count] == value) {
            count++;
        }
        compressed[compressed_size++] = value;
        compressed[compressed_size++] = count;
        i += count;
    }
    return compressed_size;
}

int rle_decompress(int compressed[], int compressed_size, int output[], int max_output_size) {
    int output_size = 0;
    for (int i = 0; i + 1 < compressed_size; i += 2) {
        int value = compressed[i];
        int count = compressed[i + 1];
        for (int j = 0; j < count; j++) {
            if (output_size >= max_output_size) return -1;
            output[output_size++] = value;
        }
    }
    return output_size;
}

void print_array(int arr[], int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) printf(", ");
    }
    printf("]\n");
}

void print_compressed(int compressed[], int size) {
    printf("[");
    for (int i = 0; i + 1 < size; i += 2) {
        printf("%d,%d", compressed[i], compressed[i + 1]);
        if (i + 2 < size) printf(",  ");
    }
    printf("]\n");
}

void run_test(const char *name, int input[], int size) {
    int compressed[size * 2];
    int output[size];

    int comp_size = rle_compress(input, size, compressed);
    int out_size  = rle_decompress(compressed, comp_size, output, size);

    printf("--- %s ---\n", name);
    printf("Исходный:        "); print_array(input, size);
    printf("Сжатый:          "); print_compressed(compressed, comp_size);
    printf("Восстановленный: "); print_array(output, out_size);

    int match = (out_size == size) && (memcmp(input, output, size * sizeof(int)) == 0);
    printf("Совпадение:     %s\n", match ? "ДА" : "НЕТ");
    printf("Коэффициент сжатия: %.1f%% (исходный: %d эл., сжатый: %d эл.)\n\n",
           (1.0 - (double)comp_size / size) * 100.0, size, comp_size);
}

int main() {
    int main_arr[] = {1,1,1,1,2,2,3,4,4,4,4,4,5,0,0,0,0,0,0,0};
    run_test("Основной пример", main_arr, sizeof(main_arr)/sizeof(main_arr[0]));

    int test1[] = {5,5,5,5,5,5,5,5,5,5};
    run_test("Тест 1: все одинаковые", test1, sizeof(test1)/sizeof(test1[0]));

    int test2[] = {1,2,3,4,5,6,7,8,9,10};
    run_test("Тест 2: все разные", test2, sizeof(test2)/sizeof(test2[0]));

    int test3[] = {1,1,2,2,1,1,2,2};
    run_test("Тест 3: чередующиеся", test3, sizeof(test3)/sizeof(test3[0]));

    return 0;
}
