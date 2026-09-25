#include <stdio.h>
#include <stdlib.h>

/*
 * Фикс: функция init возвращает указатель на выделенную память,
 * а main сохраняет результат в свою переменную arr.
 *
 * Почему было плохо: параметр int *arr в исходной функции — это
 * локальная копия указателя. malloc внутри функции записывал
 * адрес в эту копию, а arr в main оставался NULL.
 */

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
