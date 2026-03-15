#ifndef SNEAKERS_H
#define SNEAKERS_H
#define N 100
typedef struct { char brand[20]; char model[20]; int size; int price; } Sneaker;
void FillSneakers(Sneaker sneakers[N]);
void BubbleSortByPrice(Sneaker sneakers[N]);
void PrintSneakers(Sneaker sneakers[N]);
#endif
