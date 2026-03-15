#ifndef SNEAKERS_H
#define SNEAKERS_H
#include <stdlib.h>
typedef struct { char brand[20]; char model[20]; int size; int price; } Sneaker;
void FillSneakersN(Sneaker *s, int n);
void BubbleSortByPriceN(Sneaker *s, int n);
void PrintSneakersN(Sneaker *s, int n);
#endif
