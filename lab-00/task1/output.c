#include <stdio.h>

int main() {
    const int N = 555;
    const int words = 59;
    const int letters = 1004;
    const int digits = 8;
    const double a = 0.1;
    const double b = 0.2;

    printf("|%d|\n",    N);
    printf("|%8d|\n",   N);
    printf("|%-8d|\n",  N);

    printf("\n");

    printf("Words:   %6d\n",  words);
    printf("Letters: %6d\n",  letters);
    printf("Digits:  %6d\n",  digits);

    printf("\n");

    printf("a = %f; b = %f\n", a, b);
    printf("a + b = %.17f\n",  a + b);

    return 0;
}
