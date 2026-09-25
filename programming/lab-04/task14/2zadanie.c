#include <stdio.h>

// Задание 14: Найти количество единичных битов в целом неотрицательном числе a
// Используется алгоритм Брайана Кернигана: a &= (a - 1) сбрасывает младший единичный бит

int main()
{
    unsigned int a;
    printf("Введите неотрицательное целое число a: ");
    scanf("%u", &a);

    int count = 0;
    unsigned int tmp = a;
    while (tmp)
    {
        tmp &= (tmp - 1);
        count++;
    }

    printf("Количество единичных битов в числе %u: %d\n", a, count);

    return 0;
}
