/*
 * Алгоритм 9 — максимальная цифра числа
 *
 * Оригинал:
 *   for (n=a, s=0; n!=0; n=n/10) { k=n%10; if (k>s) s=k; }
 *
 * На каждой итерации отделяем последнюю цифру `k = n%10`
 * и обновляем максимум `s`. После цикла s = max цифра.
 */
#include <stdio.h>

int main(void) {
    int a;
    printf("a: ");
    if (scanf("%d", &a) != 1) {
        printf("invalid input\n");
        return 1;
    }
    if (a < 0) a = -a;  /* работаем с модулем */

    int s = 0;
    for (int n = a; n != 0; n /= 10) {
        int k = n % 10;
        if (k > s) s = k;
    }

    printf("max digit of %d = %d\n", a, s);
    return 0;
}
