/*
 * Исходный баг: #define SQR(x) x * x → SQR(y+1) = y + 1*y + 1 = 11
 *               из-за приоритета * над +.
 * Фикс: оборачиваем и аргумент, и весь макрос в скобки.
 * Найдено: внимательное чтение макроподстановки (cpp -E task3.c).
 */
#include <stdio.h>

#define SQR(x) ((x) * (x))

int main(void) {
    int y = 5;
    int z = SQR(y + 1);
    printf("z = %d\n", z);
    return 0;
}
