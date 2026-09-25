#include <stdio.h>
#include <string.h>

/*
 * Фикс: увеличиваем size буфера str и используем snprintf(),
 * чтобы никогда не выйти за границу. sprintf("%3d", 1025) пишет
 * 4 цифры + '\0' = 5 байт, что не помещается в char str[4] и
 * затирает следующее за ним поле int num.
 */

typedef struct {
    char str[16];
    int  num;
} NumberRepr;

void format(NumberRepr *number) {
    snprintf(number->str, sizeof number->str, "%3d", number->num);
}

int main(void) {
    NumberRepr number = { .num = 1025 };
    format(&number);
    printf("str: %s\n", number.str);
    printf("num: %d\n", number.num);
    return 0;
}
