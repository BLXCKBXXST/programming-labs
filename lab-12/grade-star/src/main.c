#include <stdio.h>
#include <sys/time.h>
#include "sneakers.h"

// callback-функция сравнения по цене
// возвращает > 0 если a > b, иначе <= 0
int CompareByPrice(const Sneaker *a, const Sneaker *b) {
    return a->price - b->price;
}

// сравнение по размеру
int CompareBySize(const Sneaker *a, const Sneaker *b) {
    return a->size - b->size;
}

double elapsed_ms(struct timeval start, struct timeval end) {
    return (end.tv_sec  - start.tv_sec)  * 1000.0 +
           (end.tv_usec - start.tv_usec) / 1000.0;
}

void benchmark(int n, int (*cmp)(const Sneaker *, const Sneaker *), const char *label) {
    Sneaker *arr = malloc(n * sizeof(Sneaker));
    FillSneakersN(arr, n);

    struct timeval t1, t2;
    gettimeofday(&t1, NULL);
    BubbleSortCallback(arr, n, cmp);
    gettimeofday(&t2, NULL);

    printf("N = %-8d  sort by %-8s  время: %.3f мс\n", n, label, elapsed_ms(t1, t2));
    free(arr);
}

int main(void) {
    printf("Замер BubbleSort через callback:\n");
    benchmark(100,    CompareByPrice, "price");
    benchmark(10000,  CompareByPrice, "price");
    benchmark(100000, CompareByPrice, "price");

    printf("\n");
    benchmark(100,    CompareBySize, "size");
    benchmark(10000,  CompareBySize, "size");
    benchmark(100000, CompareBySize, "size");

    Sneaker arr[100];
    FillSneakersN(arr, 100);
    printf("\nДО сортировки по цене:");
    PrintSneakersN(arr, 10);
    BubbleSortCallback(arr, 100, CompareByPrice);
    printf("\nПОСЛЕ сортировки по цене:");
    PrintSneakersN(arr, 10);

    return 0;
}
