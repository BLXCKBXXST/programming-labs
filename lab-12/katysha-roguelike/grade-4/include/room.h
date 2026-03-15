#ifndef ROOM_H
#define ROOM_H
#define N 100
typedef struct {
    char name[50];
    int  level;
    int  number;
    int  resolution;
} Room;
void FillRooms(Room rooms[N]);
void BubbleSortByLevel(Room rooms[N]);
void PrintRooms(Room rooms[N]);
#endif
