#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "room.h"

void FillRooms(Room rooms[N]) {
    char *names[] = {"Dungeon","Crypt","Throne","Library","Armory",
                     "Garden","Cave","Tower","Vault","Chapel"};
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        strcpy(rooms[i].name, names[rand()%10]);
        rooms[i].level      = 1 + rand()%10;
        rooms[i].number     = i + 1;
        rooms[i].resolution = 5 + rand()%46;
    }
}
void BubbleSortByLevel(Room rooms[N]) {
    for (int i = 0; i < N-1; i++)
        for (int j = 0; j < N-1-i; j++)
            if (rooms[j].level > rooms[j+1].level) {
                Room tmp = rooms[j]; rooms[j]=rooms[j+1]; rooms[j+1]=tmp;
            }
}
void PrintRooms(Room rooms[N]) {
    printf("\n%-5s %-12s %-8s %-8s %s\n","№","Название","Уровень","Номер","Размер");
    printf("─────────────────────────────────────────────\n");
    for (int i = 0; i < N; i++)
        printf("%-5d %-12s %-8d %-8d %d\n",i+1,rooms[i].name,rooms[i].level,rooms[i].number,rooms[i].resolution);
}
