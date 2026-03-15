#include <stdio.h>
#include "room.h"
int main(void) {
    Room rooms[N];
    FillRooms(rooms);
    printf("ДО сортировки:"); PrintRooms(rooms);
    BubbleSortByLevel(rooms);
    printf("\nПОСЛЕ сортировки по уровню:"); PrintRooms(rooms);
    return 0;
}
