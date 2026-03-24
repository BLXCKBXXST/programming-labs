#ifndef SNEAKERS_H
#define SNEAKERS_H

#define N 10  // размер массива

// описание одной пары кроссовок
typedef struct {
    char brand[20];
    char model[20];
    int  size;
    int  price;
} Sneaker;

// объявления функций (реализация в sneakers.c)
void FillSneakers(Sneaker arr[N]);
void BubbleSortByPrice(Sneaker arr[N]);
void PrintSneakers(Sneaker arr[N]);

#endif
