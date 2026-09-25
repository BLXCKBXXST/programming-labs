#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sneakers.h"
void FillSneakers(Sneaker s[N]) {
    char *b[] = {"Nike", "Adidas", "Puma"};
    char *m[] = {"Pro", "Super", "Ultra"};
    int  p[3][3] = {{200,350,500},{250,400,600},{300,450,700}};
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        int bi = rand()%3, mi = rand()%3;
        strcpy(s[i].brand, b[bi]);
        strcpy(s[i].model, m[mi]);
        s[i].size  = 36 + rand()%9;
        s[i].price = p[bi][mi];
    }
}
void BubbleSortByPrice(Sneaker s[N]) {
    for (int i = 0; i < N-1; i++)
        for (int j = 0; j < N-1-i; j++)
            if (s[j].price > s[j+1].price) {
                Sneaker t = s[j]; s[j] = s[j+1]; s[j+1] = t;
            }
}
void PrintSneakers(Sneaker s[N]) {
    printf("\n%-5s %-10s %-10s %-8s %s\n",
           "№", "Бренд", "Модель", "Размер", "Цена");
    printf("─────────────────────────────────────────────\n");
    for (int i = 0; i < N; i++)
        printf("%-5d %-10s %-10s %-8d $%d\n",
               i+1, s[i].brand, s[i].model, s[i].size, s[i].price);
}
