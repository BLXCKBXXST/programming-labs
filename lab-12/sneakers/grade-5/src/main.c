#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "sneakers.h"
double elapsed_ms(struct timeval s, struct timeval e) {
    return (e.tv_sec-s.tv_sec)*1000.0+(e.tv_usec-s.tv_usec)/1000.0;
}
void benchmark(int n) {
    Sneaker *arr = malloc(n*sizeof(Sneaker));
    FillSneakersN(arr,n);
    struct timeval t1,t2;
    gettimeofday(&t1,NULL); BubbleSortByPriceN(arr,n); gettimeofday(&t2,NULL);
    printf("N = %-8d время: %.3f мс\n",n,elapsed_ms(t1,t2));
    free(arr);
}
int main(void) {
    printf("Замер BubbleSort:\n");
    benchmark(100); benchmark(10000); benchmark(100000);
    Sneaker arr[100]; FillSneakersN(arr,100);
    printf("\nДО:"); PrintSneakersN(arr,10);
    BubbleSortByPriceN(arr,100);
    printf("\nПОСЛЕ:"); PrintSneakersN(arr,10);
    return 0;
}
