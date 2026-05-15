#ifndef SNEAKERS_H
#define SNEAKERS_H

// описание одной пары кроссовок
typedef struct {
    char brand[20];
    char model[20];
    int  size;
    int  price;
} Sneaker;

// функции принимают указатель на массив и его размер n
void FillSneakersN(Sneaker *arr, int n);
void BubbleSortByPriceN(Sneaker *arr, int n);
void PrintSneakersN(Sneaker *arr, int n);

#endif
