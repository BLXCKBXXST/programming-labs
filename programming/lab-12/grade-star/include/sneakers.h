#ifndef SNEAKERS_H
#define SNEAKERS_H

typedef struct {
    char brand[20];
    char model[20];
    int  size;
    int  price;
} Sneaker;

void FillSneakersN(Sneaker *arr, int n);
void BubbleSortCallback(Sneaker *arr, int n,
                        int (*cmp)(const Sneaker *, const Sneaker *));
void PrintSneakersN(Sneaker *arr, int n);

#endif
