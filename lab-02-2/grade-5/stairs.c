/*
 * Оценка 5. Вариант 3 (25 % 22 = 3).
 *
 * Лесенка из букв: каждая следующая строка — буква на единицу больше,
 * длина строки на единицу меньше.
 *
 * Пример N=5:
 *   AAAAA
 *   BBBB
 *   CCC
 *   DD
 *   E
 */
#include <stdio.h>

int main(void) {
    int n;
    printf("N: ");
    if (scanf("%d", &n) != 1 || n < 1 || n > 26) {
        printf("invalid N (1..26)\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        char ch = 'A' + i;
        int width = n - i;
        for (int j = 0; j < width; j++) {
            putchar(ch);
        }
        putchar('\n');
    }
    return 0;
}
