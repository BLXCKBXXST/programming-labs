#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sneakers.h"

void FillSneakers(Sneaker sneakers[N]) {
    char* brands[] = {"X", "Y", "Z"};
    char* models[] = {"Pro", "Super", "Ultra"};
    int base_prices[3][3] = {
        {200, 350, 500},
        {250, 400, 600},
        {300, 450, 700}
    };

    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        int brand_idx = rand() % 3;
        int model_idx = rand() % 3;
        strcpy(sneakers[i].brand, brands[brand_idx]);
        strcpy(sneakers[i].model, models[model_idx]);
        sneakers[i].size = 36 + (rand() % 6);
        sneakers[i].price = base_prices[brand_idx][model_idx];
    }
}

void BubbleSortSneakersByPrice(Sneaker sneakers[N]) {
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - 1 - i; j++) {
            if (sneakers[j].price > sneakers[j + 1].price) {
                Sneaker tmp = sneakers[j];
                sneakers[j] = sneakers[j + 1];
                sneakers[j + 1] = tmp;
            }
        }
    }
}

void PrintSneakers(Sneaker sneakers[N]) {
    printf("%-5s %-10s %-10s %-8s %s\n",
           "№", "Бренд", "Модель", "Размер", "Цена");
    printf("─────────────────────────────────────────────\n");
    for (int i = 0; i < 10; i++) {
        printf("%-5d %-10s %-10s %-8d $%d\n",
               i + 1,
               sneakers[i].brand,
               sneakers[i].model,
               sneakers[i].size,
               sneakers[i].price);
    }
}