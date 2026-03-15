#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "sneakers.h"
int CompareByPrice(const Sneaker *a, const Sneaker *b) { return a->price - b->price; }
int CompareBySize(const Sneaker *a, const Sneaker *b)  { return a->size  - b->size;  }
double elapsed_ms(struct timeval s, struct timeval e) {
    return (e.tv_sec-s.tv_sec)*1000.0+(e.tv_usec-s.tv_usec)/1000.0;
}
void benchmark(int n, int(*cmp)(const Sneaker*,const Sneaker*), const char *label) {
    Sneaker *arr=malloc(n*sizeof(Sneaker)); FillSneakersN(arr,n);
    struct timeval t1,t2;
    gettimeofday(&t1,NULL); BubbleSortCallback(arr,n,cmp); gettimeofday(&t2,NULL);
    printf("N=%-8d sort by %-8s %.3f мс\n",n,label,elapsed_ms(t1,t2));
    free(arr);
}
int main(void) {
    benchmark(100,CompareByPrice,"price"); benchmark(10000,CompareByPrice,"price"); benchmark(100000,CompareByPrice,"price");
    Sneaker arr[100]; FillSneakersN(arr,100);
    printf("\nДО:"); PrintSneakersN(arr,10);
    BubbleSortCallback(arr,100,CompareByPrice);
    printf("\nПОСЛЕ:"); PrintSneakersN(arr,10);
    return 0;
}
