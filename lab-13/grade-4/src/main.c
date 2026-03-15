#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sneakers.h"

int main(void) {
    Sneaker sneakers[N];

    FillSneakers(sneakers);
    PrintSneakers(sneakers);

    printf("\nBubbleSort по цене\n");
    BubbleSortSneakersByPrice(sneakers);
    PrintSneakers(sneakers);

    return 0;
}