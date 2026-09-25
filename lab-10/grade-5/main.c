/*
 * Оценка 5 — массив дробей через malloc + указатели на структуру.
 *
 * Пользователь вводит N. Программа выделяет массив из N дробей
 * через malloc, читает их, потом перемножает все: prod = f1 * f2 * ... * fN.
 */
#include <stdio.h>
#include <stdlib.h>
#include "fraction.h"

int main(void) {
    int n;
    printf("N (количество дробей): ");
    if (scanf("%d", &n) != 1 || n < 1) {
        printf("Invalid input\n");
        return 1;
    }

    Fraction *arr = malloc((size_t)n * sizeof *arr);
    if (!arr) {
        printf("oom\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("Дробь %d (a b): ", i + 1);
        read_fraction(&arr[i]);
    }

    /* перемножаем все дроби: накапливаем prod через указатели */
    Fraction prod = arr[0];
    for (int i = 1; i < n; i++) {
        prod = mul_fraction(&prod, &arr[i]);
    }

    printf("\nДроби: ");
    for (int i = 0; i < n; i++) {
        print_fraction(&arr[i]);
        printf(i + 1 == n ? "\n" : " ");
    }
    printf("Произведение всех: ");
    print_fraction(&prod);
    printf("\n");

    free(arr);
    return 0;
}
