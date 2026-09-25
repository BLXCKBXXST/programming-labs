/*
 * Алгоритм 12 — сумма цифр числа
 *
 * Оригинал:
 *   for (n=a, s=0; n!=0; n=n/10) { k=n%10; s=s+k; }
 *
 * Отщипываем последнюю цифру и прибавляем к накопителю.
 * На выходе s — сумма всех цифр исходного числа.
 *
 * 12345 -> 1+2+3+4+5 = 15
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
        s += k;
    }

    printf("digit sum of %d = %d\n", a, s);
    return 0;
}
