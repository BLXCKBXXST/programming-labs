#include <stdio.h>
#include "sneakers.h"
int main(void){
    Sneaker s[N]; FillSneakers(s);
    printf("ДО:"); PrintSneakers(s);
    BubbleSortByPrice(s);
    printf("\nПОСЛЕ:"); PrintSneakers(s);
    return 0;
}
