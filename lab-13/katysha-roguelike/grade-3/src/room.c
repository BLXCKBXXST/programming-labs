#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "room.h"
void FillRooms(Room r[N]) {
    char *names[] = {"Dungeon","Crypt","Throne","Library","Armory",
                     "Garden","Cave","Tower","Vault","Chapel"};
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        strcpy(r[i].name, names[rand()%10]);
        r[i].level      = 1 + rand()%10;
        r[i].number     = i + 1;
        r[i].resolution = 5 + rand()%46;
    }
}
void BubbleSortByLevel(Room r[N]) {
    for (int i = 0; i < N-1; i++)
        for (int j = 0; j < N-1-i; j++)
            if (r[j].level > r[j+1].level) {
                Room t = r[j]; r[j] = r[j+1]; r[j+1] = t;
            }
}
void PrintRooms(Room r[N]) {
    printf("\n%-5s %-12s %-8s %-8s %s\n",
           "№","Название","Уровень","Номер","Размер");
    printf("─────────────────────────────────────────────\n");
    for (int i = 0; i < N; i++)
        printf("%-5d %-12s %-8d %-8d %d\n",
               i+1, r[i].name, r[i].level, r[i].number, r[i].resolution);
}
