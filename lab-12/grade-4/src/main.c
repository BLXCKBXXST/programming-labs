#include <stdio.h>
#include "sneakers.h"

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
