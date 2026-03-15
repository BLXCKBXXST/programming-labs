#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "room.h"
int CompareByLevel(const Room *a, const Room *b)      { return a->level      - b->level;      }
int CompareByResolution(const Room *a, const Room *b) { return a->resolution - b->resolution; }
double elapsed_ms(struct timeval s, struct timeval e) {
    return (e.tv_sec-s.tv_sec)*1000.0+(e.tv_usec-s.tv_usec)/1000.0;
}
void benchmark(int n, int(*cmp)(const Room*,const Room*), const char *label) {
    Room *arr=malloc(n*sizeof(Room)); FillRoomsN(arr,n);
    struct timeval t1,t2;
    gettimeofday(&t1,NULL); BubbleSortCallback(arr,n,cmp); gettimeofday(&t2,NULL);
    printf("N=%-8d sort by %-12s %.3f мс\n",n,label,elapsed_ms(t1,t2));
    free(arr);
}
int main(void) {
    benchmark(100,CompareByLevel,"level"); benchmark(10000,CompareByLevel,"level"); benchmark(100000,CompareByLevel,"level");
    Room arr[100]; FillRoomsN(arr,100);
    printf("\nДО (по level):"); PrintRoomsN(arr,10);
    BubbleSortCallback(arr,100,CompareByLevel);
    printf("\nПОСЛЕ (по level):"); PrintRoomsN(arr,10);
    return 0;
}
