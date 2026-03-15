#ifndef SNEAKERS_H
#define SNEAKERS_H

typedef struct {
    char brand[20];
    char model[20];
    int  size;
    int  price;
} Sneaker;

void FillSneakersN(Sneaker *sneakers, int n);
void BubbleSortByPriceN(Sneaker *sneakers, int n);
void PrintSneakersN(Sneaker *sneakers, int n);

#endif /* SNEAKERS_H */
