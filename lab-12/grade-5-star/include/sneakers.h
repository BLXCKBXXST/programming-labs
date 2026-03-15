#ifndef SNEAKERS_H
#define SNEAKERS_H

#include <stdlib.h>

typedef struct {
    char brand[20];
    char model[20];
    int  size;
    int  price;
} Sneaker;

void FillSneakersN(Sneaker *sneakers, int n);

// callback здесь - функция принимает указатель на функцию сравнения
void BubbleSortCallback(Sneaker *sneakers, int n,
                        int (*cmp)(const Sneaker *, const Sneaker *));
void PrintSneakersN(Sneaker *sneakers, int n);

#endif /* SNEAKERS_H */
