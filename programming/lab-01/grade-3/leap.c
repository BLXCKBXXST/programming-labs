#include <stdio.h>

int main(void) {
    int year;
    printf("Year: ");
    if (scanf("%d", &year) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    int leap;
    if (year % 400 == 0) {
        leap = 1;
    } else if (year % 100 == 0) {
        leap = 0;
    } else if (year % 4 == 0) {
        leap = 1;
    } else {
        leap = 0;
    }

    printf("%s\n", leap ? "YES" : "NO");
    return 0;
}
