/*
 * Алгоритм 10 — разворот цифр числа
 *
 * Оригинал:
 *   for (n=a, s=0; n!=0; n=n/10) { k=n%10; s=s*10+k; }
 *
 * Отщипываем последнюю цифру `k = n%10` и пристраиваем её
 * к новому числу `s = s*10 + k`. На выходе s — число, в котором
 * цифры записаны в обратном порядке.
 *
 * 12345 -> 54321
 */
#include <stdio.h>

int main(void) {
    int a;
    printf("a: ");
    if (scanf("%d", &a) != 1) {
        printf("invalid input\n");
        return 1;
    }
    if (a < 0) a = -a;

    int s = 0;
    for (int n = a; n != 0; n /= 10) {
        int k = n % 10;
        s = s * 10 + k;
    }

    printf("reverse(%d) = %d\n", a, s);
    return 0;
}
