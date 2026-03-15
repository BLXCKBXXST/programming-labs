#ifndef ROOM_H
#define ROOM_H
typedef struct {
    char name[50];
    int  level;
    int  number;
    int  resolution;
} Room;
void FillRoomsN(Room *r, int n);
void BubbleSortByLevelN(Room *r, int n);
void PrintRoomsN(Room *r, int n);
#endif
