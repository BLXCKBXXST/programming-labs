#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "room.h"
void FillRoomsN(Room *r, int n) {
    char *names[]={"Dungeon","Crypt","Throne","Library","Armory",
                   "Garden","Cave","Tower","Vault","Chapel"};
    srand(time(NULL));
    for(int i=0;i<n;i++){
        strcpy(r[i].name,names[rand()%10]);
        r[i].level=1+rand()%10; r[i].number=i+1; r[i].resolution=5+rand()%46;
    }
}
void BubbleSortCallback(Room *r, int n, int(*cmp)(const Room*,const Room*)) {
    for(int i=0;i<n-1;i++) for(int j=0;j<n-1-i;j++)
        if(cmp(&r[j],&r[j+1])>0){Room t=r[j];r[j]=r[j+1];r[j+1]=t;}
}
void PrintRoomsN(Room *r, int n) {
    printf("\n%-5s %-12s %-8s %-8s %s\n","№","Название","Уровень","Номер","Размер");
    printf("─────────────────────────────────────────────\n");
    for(int i=0;i<n;i++) printf("%-5d %-12s %-8d %-8d %d\n",i+1,r[i].name,r[i].level,r[i].number,r[i].resolution);
}
