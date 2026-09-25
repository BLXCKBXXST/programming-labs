/*
 * Оценка 4. Квадрат N×N из чисел 1..N*N построчно.
 *
 * Пример N=3:
 *   1 2 3
 *   4 5 6
 *   7 8 9
 */
#include <stdio.h>

int main(void) {
    int n;
    printf("N: ");
    if (scanf("%d", &n) != 1 || n < 1 || n > 20) {
        printf("invalid N (1..20)\n");
        return 1;
    }

    int val = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d", val);
            val++;
            if (j == n - 1) {
                printf("\n");
            } else {
                printf(" ");
            }
        }
    }
    return 0;
}
