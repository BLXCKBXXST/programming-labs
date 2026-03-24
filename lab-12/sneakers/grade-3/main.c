#include <stdio.h>
#include <stdlib.h>   // rand(), srand()
#include <string.h>   // strcpy()
#include <time.h>     // time() — чтобы каждый раз были разные числа

#define N 10   // сколько кроссовок в массиве

// Структура — описание одной пары кроссовок
typedef struct {
    char brand[20];  // бренд, например "Nike"
    char model[20];  // модель, например "Air Max"
    int  size;       // размер: 36–44
    int  price;      // цена в долларах
} Sneaker;

// Заполняем массив случайными кроссовками
void FillSneakers(Sneaker arr[N]) {
    char *brands[] = {"Nike", "Adidas", "Puma", "Reebok"};
    char *models[] = {"Air Max", "Ultraboost", "Classic", "Suede"};

    srand(time(NULL));  // инициализируем генератор случайных чисел

    for (int i = 0; i < N; i++) {
        int b = rand() % 4;  // случайный индекс бренда (0..3)
        int m = rand() % 4;  // случайный индекс модели (0..3)

        strcpy(arr[i].brand, brands[b]);
        strcpy(arr[i].model, models[m]);
        arr[i].size  = 36 + rand() % 9;    // размер от 36 до 44
        arr[i].price = 50 + rand() % 451;  // цена от 50 до 500
    }
}

// Красиво выводим массив в виде таблицы
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

// Сортировка пузырьком по цене (от дешёвых к дорогим)
// Идея: на каждом проходе сравниваем соседей и меняем местами если надо
// Самый дорогой «всплывает» в конец — как пузырёк
void BubbleSortByPrice(Sneaker arr[N]) {
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - 1 - i; j++) {
            if (arr[j].price > arr[j + 1].price) {
                // меняем местами два соседних элемента
                Sneaker tmp = arr[j];
                arr[j]     = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

int main(void) {
    Sneaker sneakers[N];

    FillSneakers(sneakers);

    printf("ДО сортировки:");
    PrintSneakers(sneakers);

    BubbleSortByPrice(sneakers);

    printf("\nПОСЛЕ сортировки по цене:");
    PrintSneakers(sneakers);

    return 0;
}
