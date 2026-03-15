#ifndef ROOM_H
#define ROOM_H
#include <stdlib.h>
typedef struct {
    char name[50];
    int  level;
    int  number;
    int  resolution;
} Room;
void FillRoomsN(Room *r, int n);
void BubbleSortCallback(Room *r, int n, int(*cmp)(const Room*,const Room*));
void PrintRoomsN(Room *r, int n);
#endif
