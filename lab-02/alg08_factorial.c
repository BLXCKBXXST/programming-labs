/*
 * Алгоритм 8 — факториал n!
 *
 * Оригинал:
 *   for (s=1, i=1; i<=n; i++) s = s * i;
 *
 * Накопитель s стартует с 1 и последовательно умножается на 1, 2, ..., n.
 * Итог: s = n!
 */
#include <stdio.h>

int main(void) {
    int n;
    long long s = 1;

    printf("n: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("invalid input\n");
        return 1;
    }

    for (int i = 1; i <= n; i++) {
        s = s * i;
    }

    printf("%d! = %lld\n", n, s);
    return 0;
}
