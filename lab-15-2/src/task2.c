/*
 * Исходный баг: sprintf(number->str, "%3d", 1025) пишет 5 байт ("1025\0")
 *               в char str[4], затирая первый байт следующего поля num.
 * Фикс: str увеличен до 16 байт, заменён sprintf -> snprintf для безопасности.
 * Найдено: AddressSanitizer (stack-buffer-overflow в format()).
 */
#include <stdio.h>
#include <string.h>

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
