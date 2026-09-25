#include <stdio.h>

/*
 * Фикс: оборачиваем и весь макрос, и каждый аргумент в скобки.
 *
 * Было: #define SQR(x) x * x
 *   SQR(y + 1)  →  y + 1 * y + 1  →  5 + 1*5 + 1 = 11
 *
 * Стало: умножение применяется к целому (y + 1), а не к 1 и y отдельно.
 */
#define SQR(x) ((x) * (x))

int main(void) {
    int y = 5;
    int z = SQR(y + 1);
    printf("z = %d\n", z);
    return 0;
}
