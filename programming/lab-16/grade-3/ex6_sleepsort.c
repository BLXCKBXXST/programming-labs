/*
 * Упражнение 6 — Sleepsort, асимптотика O(N) (по времени)
 *
 * Идея: на каждый элемент массива запускается поток, который засыпает
 * на (value) единиц времени, после чего печатает значение. Большие
 * числа проснутся позже — значения напечатаются в отсортированном порядке.
 *
 * Здесь "единица" = 50 миллисекунд (через usleep), чтобы маленькие числа
 * не сливались. Массив целых, до 50 элементов и значения 1..200.
 */
#define _DEFAULT_SOURCE   /* для usleep() и useconds_t */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define UNIT_US 50000   /* 50 ms */

void *sleeper(void *arg) {
    int v = *(int *)arg;
    if (v > 0) usleep((unsigned int)v * UNIT_US);
    printf("%d\n", v);
    return NULL;
}

int main(int argc, char *argv[]) {
    int data[] = {5, 2, 8, 1, 3, 7, 6, 4, 10, 9};
    int n = (int)(sizeof data / sizeof data[0]);

    /* можно передать массив через CLI: ./ex6_sleepsort 7 3 9 1 */
    int cli[64];
    if (argc > 1) {
        n = argc - 1 < 64 ? argc - 1 : 64;
        for (int i = 0; i < n; i++) cli[i] = atoi(argv[i + 1]);
    }
    int *src = (argc > 1) ? cli : data;

    pthread_t tids[64];
    for (int i = 0; i < n; i++) {
        pthread_create(&tids[i], NULL, sleeper, &src[i]);
    }
    for (int i = 0; i < n; i++) {
        pthread_join(tids[i], NULL);
    }
    return 0;
}
