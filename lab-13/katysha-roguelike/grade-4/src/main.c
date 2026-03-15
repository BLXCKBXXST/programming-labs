#include <stdio.h>
#include "room.h"
int main(void){
    Room r[N]; FillRooms(r);
    printf("ДО:"); PrintRooms(r);
    BubbleSortByLevel(r);
    printf("\nПОСЛЕ:"); PrintRooms(r);
    return 0;
}
