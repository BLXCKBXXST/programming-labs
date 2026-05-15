# Задача 2 — Buffer overflow затирает соседнее поле

## Симптом

```
$ ./before
str: 1025
num: 0       ← а должно быть 1025
```

`number.num` после вызова `format()` стал не `1025`, хотя его никто не менял.

## Почему

[before.c](before.c) — структура:

```c
typedef struct {
    char str[4];   ← всего 4 байта
    int  num;
} NumberRepr;

void format(NumberRepr *number) {
    sprintf(number->str, "%3d", number->num);   ← пишет 4 цифры + '\0'
}
```

Число `1025` форматируется в `"1025"` — это **4 символа плюс терминальный `\0`** = 5 байт. В `str[4]` помещается только 4 — пятый байт (`\0`) уходит **за границу буфера** и попадает в первый байт следующего поля `num`. На x86 little-endian это младший байт `int`, и значение `num` становится `1025 & 0xFFFFFF00 = 1024`. А если в форматирование попадает много нулей — может вообще обнулиться.

> Это **buffer overflow** — классическая дыра в C. AddressSanitizer (`gcc -fsanitize=address`) сразу её ловит.

## Фикс

[after.c](after.c) — увеличить буфер и использовать `snprintf` (он не пишет больше, чем `size`):

```c
typedef struct {
    char str[16];   ← хватит на любое int
    int  num;
} NumberRepr;

void format(NumberRepr *number) {
    snprintf(number->str, sizeof number->str, "%3d", number->num);
}
```

Два правила:
1. Размер буфера выбираем с запасом — для `int` максимум 11 символов (`"-2147483648"`) + `\0`.
2. Используем **`snprintf`** вместо `sprintf` — он принимает максимальный размер и обрежет, если не помещается, но никогда не выйдет за границу.

## Проверка

```bash
gcc after.c -o after && ./after
# str: 1025
# num: 1025
```

> Полезные инструменты диагностики:
> ```bash
> gcc -fsanitize=address before.c -o before-asan && ./before-asan
> # AddressSanitizer покажет точную строку, где произошёл overflow
> ```
