#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/sneakers.h"

void FillSneakersN(Sneaker *arr, int n) {
    char *brands[] = {"Nike", "Adidas", "Puma", "Reebok"};
    char *models[] = {"Air Max", "Ultraboost", "Classic", "Suede"};

    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        int b = rand() % 4;
        int m = rand() % 4;
        strcpy(arr[i].brand, brands[b]);
        strcpy(arr[i].model, models[m]);
        arr[i].size  = 36 + rand() % 9;
        arr[i].price = 50 + rand() % 451;
    }
}

// сортировка пузырьком с callback-функцией сравнения
// cmp — это указатель на функцию, которую мы передаём снаружи
// она принимает два кроссовка и говорит: первый «больше»? (>0) или нет (<=0)
void BubbleSortCallback(Sneaker *arr, int n,
                        int (*cmp)(const Sneaker *, const Sneaker *)) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (cmp(&arr[j], &arr[j + 1]) > 0) {
                Sneaker tmp  = arr[j];
                arr[j]       = arr[j + 1];
                arr[j + 1]   = tmp;
            }
        }
    }
}

void PrintSneakersN(Sneaker *arr, int n) {
    printf("\n%-4s %-10s %-12s %-8s %s\n",
           "№", "Бренд", "Модель", "Размер", "Цена");
    printf("-------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-4d %-10s %-12s %-8d $%d\n",
               i + 1,
               arr[i].brand,
               arr[i].model,
               arr[i].size,
               arr[i].price);
    }
}
