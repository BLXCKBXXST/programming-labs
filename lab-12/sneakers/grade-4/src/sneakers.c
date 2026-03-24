#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/sneakers.h"

// Заполняем массив случайными кроссовками
void FillSneakers(Sneaker arr[N]) {
    char *brands[] = {"Nike", "Adidas", "Puma", "Reebok"};
    char *models[] = {"Air Max", "Ultraboost", "Classic", "Suede"};

    srand(time(NULL));

    for (int i = 0; i < N; i++) {
        int b = rand() % 4;
        int m = rand() % 4;
        strcpy(arr[i].brand, brands[b]);
        strcpy(arr[i].model, models[m]);
        arr[i].size  = 36 + rand() % 9;
        arr[i].price = 50 + rand() % 451;
    }
}

// Сортировка пузырьком по полю price
void BubbleSortByPrice(Sneaker arr[N]) {
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - 1 - i; j++) {
            if (arr[j].price > arr[j + 1].price) {
                Sneaker tmp = arr[j];
                arr[j]     = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

// Вывод массива в виде таблицы
void PrintSneakers(Sneaker arr[N]) {
    printf("\n%-4s %-10s %-12s %-8s %s\n",
           "№", "Бренд", "Модель", "Размер", "Цена");
    printf("-------------------------------------------\n");
    for (int i = 0; i < N; i++) {
        printf("%-4d %-10s %-12s %-8d $%d\n",
               i + 1,
               arr[i].brand,
               arr[i].model,
               arr[i].size,
               arr[i].price);
    }
}
