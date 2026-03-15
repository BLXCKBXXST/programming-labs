#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 100

typedef struct {
    char brand[20];
    char model[20];
    int  size;
    int  price;
} Sneaker;

void FillSneakers(Sneaker sneakers[N]) {
    char *brands[] = {"Nike", "Adidas", "Puma"};
    char *models[] = {"Pro", "Super", "Ultra"};
    int base_prices[3][3] = {
        {200, 350, 500},
        {250, 400, 600},
        {300, 450, 700}
    };
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        int b = rand() % 3;
        int m = rand() % 3;
        strcpy(sneakers[i].brand, brands[b]);
        strcpy(sneakers[i].model, models[m]);
        sneakers[i].size  = 36 + (rand() % 9);
        sneakers[i].price = base_prices[b][m];
    }
}

void PrintSneakers(Sneaker sneakers[N]) {
    printf("\n%-5s %-10s %-10s %-8s %s\n",
           "№", "Бренд", "Модель", "Размер", "Цена");
    printf("─────────────────────────────────────────────\n");
    for (int i = 0; i < N; i++) {
        printf("%-5d %-10s %-10s %-8d $%d\n",
               i+1, sneakers[i].brand, sneakers[i].model,
               sneakers[i].size, sneakers[i].price);
    }
}

// сортировка пузырьком по цене
// на каждом проходе самый дорогой «всплывает» в конец, O(n²)
void BubbleSortByPrice(Sneaker sneakers[N]) {
    for (int i = 0; i < N - 1; i++)
        for (int j = 0; j < N - 1 - i; j++)
            if (sneakers[j].price > sneakers[j+1].price) {
                Sneaker tmp = sneakers[j];
                sneakers[j] = sneakers[j+1];
                sneakers[j+1] = tmp;
            }
}

int main(void) {
    Sneaker sneakers[N];
    FillSneakers(sneakers);
    printf("ДО сортировки:"); PrintSneakers(sneakers);
    BubbleSortByPrice(sneakers);
    printf("\nПОСЛЕ сортировки по цене:"); PrintSneakers(sneakers);
    return 0;
}
