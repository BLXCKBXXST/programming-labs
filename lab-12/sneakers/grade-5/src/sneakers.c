#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sneakers.h"
void FillSneakersN(Sneaker *s, int n) {
    char *brands[]={"Ника","Адидас","Пума"}; char *models[]={"Pro","Super","Ultra"};
    int p[3][3]={{200,350,500},{250,400,600},{300,450,700}};
    srand(time(NULL));
    for(int i=0;i<n;i++){int b=rand()%3,m=rand()%3;
        strcpy(s[i].brand,brands[b]); strcpy(s[i].model,models[m]);
        s[i].size=36+rand()%9; s[i].price=p[b][m];}
}
void BubbleSortByPriceN(Sneaker *s, int n) {
    for(int i=0;i<n-1;i++) for(int j=0;j<n-1-i;j++)
        if(s[j].price>s[j+1].price){Sneaker t=s[j];s[j]=s[j+1];s[j+1]=t;}
}
void PrintSneakersN(Sneaker *s, int n) {
    printf("\n%-5s %-10s %-10s %-8s %s\n","№","Бренд","Модель","Размер","Цена");
    printf("─────────────────────────────────────────────\n");
    for(int i=0;i<n;i++) printf("%-5d %-10s %-10s %-8d $%d\n",i+1,s[i].brand,s[i].model,s[i].size,s[i].price);
}
