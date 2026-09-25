# Задание 2 — Переполнение целых типов

Что произойдёт, если выйти за границу диапазона `int`, `unsigned int` или `char`?

## Что в коде

```c
int max = INT_MAX;          // 2 147 483 647
printf("%d\n", max + 1);    // переполнение signed

unsigned int u = 0;
u = u - 1;
printf("%u\n", u);          // wrap-around у unsigned

char min = CHAR_MIN;        // -128
printf("%hhd\n", min - 1);  // переполнение char
```

## Эталонный вывод

```
INT_MAX        = 2147483647
INT_MAX + 1    = -2147483648
0u - 1 (%u)    = 4294967295
CHAR_MIN       = -128
CHAR_MIN - 1   = 127
```

## Почему так получилось

| Операция | Что по стандарту | Что на x86 |
|---|---|---|
| `INT_MAX + 1` | **undefined behavior** (UB) для знакового переполнения | компилятор обычно оставляет wrap two's-complement, результат = `INT_MIN` |
| `0u - 1` | **определённое** поведение: значение по модулю 2³² | = `UINT_MAX` = `4294967295` |
| `CHAR_MIN - 1` | UB (если `char` знаковый) | wrap: `-128 → 127` |

> Никогда не полагайтесь на конкретный результат UB. `gcc -fsanitize=undefined` покажет, в какой строке произошло переполнение.

## Спецификаторы

| Тип | Спецификатор |
|---|---|
| `int` | `%d` |
| `unsigned int` | `%u` |
| `char` (знаковый) | `%hhd` |
| `unsigned char` | `%hhu` |

## Заголовок

`<limits.h>` содержит макросы `INT_MAX`, `INT_MIN`, `CHAR_MIN`, `CHAR_MAX`, `UINT_MAX` и т.д.
