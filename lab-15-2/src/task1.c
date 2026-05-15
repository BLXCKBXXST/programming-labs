/*
 * Исходный баг: указатель передавался в init() по значению,
 *               malloc писал в локальную копию, в main() arr остался NULL.
 * Фикс: init() возвращает указатель, main сохраняет результат.
 * Найдено: AddressSanitizer (heap-buffer-overflow на NULL pointer).
 */
#include <stdio.h>
#include <stdlib.h>

int *init(int n) {
    int *arr = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }
    return arr;
}

int main(void) {
    int n = 10;
    int *arr = init(n);

    for (int i = 0; i < n; i++) {
        printf("%d\n", arr[i]);
    }
    free(arr);
    return 0;
}
