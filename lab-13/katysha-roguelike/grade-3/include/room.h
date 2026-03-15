#ifndef ROOM_H
#define ROOM_H
#define N 100
typedef struct {
    char name[50];
    int  level;
    int  number;
    int  resolution;
} Room;
void FillRooms(Room r[N]);
void BubbleSortByLevel(Room r[N]);
void PrintRooms(Room r[N]);
#endif
