#include <stdio.h>
#include <sys/time.h>
#include "sneakers.h"

// возвращает разницу времени в миллисекундах
double elapsed_ms(struct timeval start, struct timeval end) {
    return (end.tv_sec  - start.tv_sec)  * 1000.0 +
           (end.tv_usec - start.tv_usec) / 1000.0;
}

void benchmark(int n) {
    // выделяем массив динамически потому что n меняется
    Sneaker *sneakers = malloc(n * sizeof(Sneaker));
    FillSneakersN(sneakers, n);

    struct timeval t1, t2;
    gettimeofday(&t1, NULL);
    BubbleSortByPriceN(sneakers, n);
    gettimeofday(&t2, NULL);

    printf("N = %-8d  время: %.3f мс\n", n, elapsed_ms(t1, t2));
    free(sneakers);
}

int main(void) {
    // замеряем для трёх размеров как сказано в задании
    printf("Замер времени BubbleSort:\n");
    benchmark(100);
    benchmark(10000);
    benchmark(100000);

    // демо: вывод первых 10 записей
    Sneaker sneakers[100];
    FillSneakersN(sneakers, 100);
    printf("\nДО сортировки:");
    PrintSneakersN(sneakers, 10);
    BubbleSortByPriceN(sneakers, 100);
    printf("\nПОСЛЕ сортировки:");
    PrintSneakersN(sneakers, 10);

    return 0;
}
