#include <stdio.h>
#include <limits.h>

int main() {
    int max = INT_MAX;
    printf("INT_MAX        = %d\n", max);
    printf("INT_MAX + 1    = %d   (переполнение signed -> UB, обычно -2147483648)\n", max + 1);

    unsigned int u = 0;
    u = u - 1;
    printf("0u - 1 (%%u)    = %u   (wrap-around у unsigned определён)\n", u);

    char min = CHAR_MIN;
    char shifted = (char)(min - 1);
    printf("CHAR_MIN       = %hhd\n", min);
    printf("CHAR_MIN - 1   = %hhd  (переполнение char -> UB, обычно %d)\n", shifted, CHAR_MAX);

    return 0;
}
