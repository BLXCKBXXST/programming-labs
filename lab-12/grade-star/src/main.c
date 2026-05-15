#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "../include/sneakers.h"

// функция сравнения по цене — возвращает >0 если a дороже b
int CompareByPrice(const Sneaker *a, const Sneaker *b) {
    return a->price - b->price;
}

// функция сравнения по размеру — возвращает >0 если размер a больше b
int CompareBySize(const Sneaker *a, const Sneaker *b) {
    return a->size - b->size;
}

double elapsed_ms(struct timeval start, struct timeval end) {
    return (end.tv_sec - start.tv_sec) * 1000.0
         + (end.tv_usec - start.tv_usec) / 1000.0;
}

void benchmark(int n, int (*cmp)(const Sneaker *, const Sneaker *),
               const char *label) {
    Sneaker *arr = malloc(n * sizeof(Sneaker));
    FillSneakersN(arr, n);

    struct timeval t1, t2;
    gettimeofday(&t1, NULL);
    BubbleSortCallback(arr, n, cmp);
    gettimeofday(&t2, NULL);

    printf("N = %-8d  сортировка по %-8s  %.3f мс\n",
           n, label, elapsed_ms(t1, t2));
    free(arr);
}

int main(void) {
    printf("--- Замер BubbleSort с callback ---\n");
    benchmark(100,    CompareByPrice, "цене");
    benchmark(10000,  CompareByPrice, "цене");
    benchmark(100000, CompareByPrice, "цене");

    printf("\n");
    benchmark(100,    CompareBySize, "размеру");
    benchmark(10000,  CompareBySize, "размеру");

    // показываем наглядный пример
    Sneaker arr[10];
    FillSneakersN(arr, 10);

    printf("\nПример сортировки по ЦЕНЕ (10 кроссовок):");
    printf("\nДО:");
    PrintSneakersN(arr, 10);

    BubbleSortCallback(arr, 10, CompareByPrice);
    printf("\nПОСЛЕ:");
    PrintSneakersN(arr, 10);

    // сортируем ещё раз — теперь по размеру
    FillSneakersN(arr, 10);
    printf("\nПример сортировки по РАЗМЕРУ:");
    printf("\nДО:");
    PrintSneakersN(arr, 10);

    BubbleSortCallback(arr, 10, CompareBySize);
    printf("\nПОСЛЕ:");
    PrintSneakersN(arr, 10);

    return 0;
}
