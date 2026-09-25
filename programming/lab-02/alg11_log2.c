/*
 * Алгоритм 11 — целая часть двоичного логарифма: floor(log2(n))
 *
 * Оригинал:
 *   for (k=0, m=1; m <= n; k++, m = m * 2);
 *   printf("%d", k-1);
 *
 * Удваиваем m, пока m ≤ n, и считаем шаги k. После цикла m — первое
 * значение строго больше n, причём m = 2^k. То есть 2^(k-1) ≤ n < 2^k,
 * следовательно k-1 = floor(log2(n)).
 *
 * n=8  -> 3   (log2 8  = 3)
 * n=10 -> 3   (log2 10 ≈ 3.32, floor = 3)
 * n=1  -> 0
 */
#include <stdio.h>

int main(void) {
    int n;
    printf("n: ");
    if (scanf("%d", &n) != 1 || n < 1) {
        printf("invalid input (need n >= 1)\n");
        return 1;
    }

    int k, m;
    for (k = 0, m = 1; m <= n; k++, m = m * 2);

    printf("floor(log2(%d)) = %d\n", n, k - 1);
    return 0;
}
