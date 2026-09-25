#include <stdio.h>
#include "../include/sneakers.h"

// главная функция — только вызываем готовые функции из sneakers.c
int main(void) {
    Sneaker sneakers[N];

    FillSneakers(sneakers);

    printf("ДО сортировки:");
    PrintSneakers(sneakers);

    BubbleSortByPrice(sneakers);

    printf("\nПОСЛЕ сортировки по цене:");
    PrintSneakers(sneakers);

    return 0;
}
