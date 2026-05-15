#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>   // gettimeofday()
#include "../include/sneakers.h"

// считаем сколько миллисекунд прошло между двумя моментами времени
double elapsed_ms(struct timeval start, struct timeval end) {
    double sec  = (double)(end.tv_sec  - start.tv_sec);
    double usec = (double)(end.tv_usec - start.tv_usec);
    return sec * 1000.0 + usec / 1000.0;
}

// создаём массив из n элементов, сортируем и замеряем время
void benchmark(int n) {
    // malloc — выделяем память под n кроссовок динамически
    Sneaker *arr = malloc(n * sizeof(Sneaker));

    FillSneakersN(arr, n);

    struct timeval t1, t2;
    gettimeofday(&t1, NULL);        // запомнили время ДО
    BubbleSortByPriceN(arr, n);     // сортируем
    gettimeofday(&t2, NULL);        // запомнили время ПОСЛЕ

    printf("N = %-8d  время сортировки: %.3f мс\n", n, elapsed_ms(t1, t2));

    free(arr);  // освобождаем память — обязательно!
}

int main(void) {
    // замеряем время для разных размеров
    printf("--- Замер BubbleSort ---\n");
    benchmark(100);
    benchmark(10000);
    benchmark(100000);

    // показываем пример сортировки на 10 элементах
    Sneaker arr[10];
    FillSneakersN(arr, 10);

    printf("\nПример (10 кроссовок):")
    printf("\nДО сортировки:");
    PrintSneakersN(arr, 10);

    BubbleSortByPriceN(arr, 10);

    printf("\nПОСЛЕ сортировки:");
    PrintSneakersN(arr, 10);

    return 0;
}
