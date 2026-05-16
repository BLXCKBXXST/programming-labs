# Оценка 5 — Указатели на структуру + динамическая память

## Что добавилось по сравнению с grade-4

- Функции принимают **`const Fraction *`** вместо `Fraction` — экономим копирование.
- Массив дробей **выделяется через `malloc`** в runtime: размер N задаётся пользователем.
- Память освобождается через `free()` в конце программы.

## Файлы

| Файл | Что внутри |
|---|---|
| [fraction.h](fraction.h) | typedef + прототипы (все через указатели) |
| [fraction.c](fraction.c) | реализация `read/print/mul/div` |
| [main.c](main.c) | malloc массива, ввод, перемножение, free |

## Идея

```c
Fraction *arr = malloc(n * sizeof *arr);   /* массив на N дробей */
read_fraction(&arr[i]);                     /* передаём указатель */
prod = mul_fraction(&prod, &arr[i]);        /* указатели вместо копий */
free(arr);                                  /* обязательно освободить */
```

## Сборка и запуск

```bash
gcc main.c fraction.c -o fraction_dyn
./fraction_dyn
# N (количество дробей): 3
# Дробь 1 (a b): 1 2
# Дробь 2 (a b): 3 4
# Дробь 3 (a b): 5 6
#
# Дроби: 1/2 3/4 5/6
# Произведение всех: 15/48
```

## 📸 Скриншот запуска

![Запуск grade-5](run.png)

## Почему указатели

| Вариант | Что копируется при вызове |
|---|---|
| `mul_fraction(Fraction x, Fraction y)` | вся структура × 2 раза |
| `mul_fraction(const Fraction *x, const Fraction *y)` | два указателя (8 байт каждый) |

На `Fraction` (8 байт) разница не заметна. Но на крупных структурах (например, матрица 100×100 = 40 кБ) копирование «по значению» убивает производительность.

## Что проверяет ASan

Если запустить `gcc -fsanitize=address main.c fraction.c`, и убрать `free(arr)` — санитайзер при выходе напишет:

```
==12345==ERROR: LeakSanitizer: detected memory leaks
Direct leak of 24 byte(s) in 1 object(s) allocated from:
    #0 malloc
    #1 main main.c:16
```

Полезно для отлова утечек на больших проектах.
