#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "room.h"
double elapsed_ms(struct timeval s, struct timeval e) {
    return (e.tv_sec-s.tv_sec)*1000.0+(e.tv_usec-s.tv_usec)/1000.0;
}
void benchmark(int n) {
    Room *arr = malloc(n*sizeof(Room));
    FillRoomsN(arr,n);
    struct timeval t1,t2;
    gettimeofday(&t1,NULL); BubbleSortByLevelN(arr,n); gettimeofday(&t2,NULL);
    printf("N = %-8d время: %.3f мс\n",n,elapsed_ms(t1,t2));
    free(arr);
}
int main(void) {
    printf("Замер BubbleSort по уровню:\n");
    benchmark(100); benchmark(10000); benchmark(100000);
    Room arr[100]; FillRoomsN(arr,100);
    printf("\nДО:"); PrintRoomsN(arr,10);
    BubbleSortByLevelN(arr,100);
    printf("\nПОСЛЕ:"); PrintRoomsN(arr,10);
    return 0;
}
