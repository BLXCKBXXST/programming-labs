#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sneakers.h"

void FillSneakersN(Sneaker *sneakers, int n) {
    char *brands[] = {"Nike", "Adidas", "Puma"};
    char *models[] = {"Pro", "Super", "Ultra"};
    int base_prices[3][3] = {
        {200, 350, 500},
        {250, 400, 600},
        {300, 450, 700}
    };

    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        int b = rand() % 3;
        int m = rand() % 3;
        strcpy(sneakers[i].brand, brands[b]);
        strcpy(sneakers[i].model, models[m]);
        sneakers[i].size  = 36 + (rand() % 9);
        sneakers[i].price = base_prices[b][m];
    }
}

// сортировка с callback:
// cmp - это указатель на функцию которая знает как сравнивать два элемента
// благодаря этому можно сортировать по любому полю не меняя саму функцию сортировки
void BubbleSortCallback(Sneaker *sneakers, int n,
                        int (*cmp)(const Sneaker *, const Sneaker *)) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (cmp(&sneakers[j], &sneakers[j + 1]) > 0) {
                Sneaker tmp      = sneakers[j];
                sneakers[j]     = sneakers[j + 1];
                sneakers[j + 1] = tmp;
            }
        }
    }
}

void PrintSneakersN(Sneaker *sneakers, int n) {
    printf("\n%-5s %-10s %-10s %-8s %s\n",
           "№", "Бренд", "Модель", "Размер", "Цена");
    printf("─────────────────────────────────────────────\n");
    for (int i = 0; i < n; i++) {
        printf("%-5d %-10s %-10s %-8d $%d\n",
               i + 1,
               sneakers[i].brand,
               sneakers[i].model,
               sneakers[i].size,
               sneakers[i].price);
    }
}
