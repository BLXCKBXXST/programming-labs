#ifndef SNEAKERS_H
#define SNEAKERS_H

typedef struct {
    char brand[10];
    char model[10];
    int size;
    int price;
} Sneaker;

#define N 100

void FillSneakers(Sneaker sneakers[N]);
void BubbleSortSneakersByPrice(Sneaker sneakers[N]);
void PrintSneakers(Sneaker sneakers[N]);

#endif /* SNEAKERS_H */