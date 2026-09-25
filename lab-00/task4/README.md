# Задание 4 — Поиск ошибок при компиляции

Дан код, который **не компилируется**. Нужно исправить его так, чтобы вывод стал:

```
The square root of 0.500000 is 0.707107
```

## Исходный код (с ошибками) — [before.c](before.c)

```c
include <studio.h>
#include <math.h>

main()
{
    x = 5;
    int result = sqrt(x);
    print(The square root of %lf is %lf\n", x, result);
    return 0;
}
```

## Что не так

| № | Ошибка | Исправление |
|---|---|---|
| 1 | `include <studio.h>` — нет решётки и опечатка | `#include <stdio.h>` |
| 2 | `main()` без типа возвращаемого значения | `int main(void)` |
| 3 | `x = 5;` без объявления типа | `double x = 0.5;` (и значение поменять, иначе результат будет `sqrt(5)` ≈ 2.236, а не 0.707) |
| 4 | `int result = sqrt(x);` — `sqrt` возвращает `double` | `double result = sqrt(x);` |
| 5 | `print` вместо `printf` | `printf` |
| 6 | Пропущена открывающая кавычка `"` | `printf("The square...")` |

Плюс: при компиляции нужен ключ **`-lm`**, иначе линкер не найдёт `sqrt`:

```
/usr/bin/ld: undefined reference to `sqrt'
```

## Исправленный код — [after.c](after.c)

```c
#include <stdio.h>
#include <math.h>

int main(void) {
    double x = 0.5;
    double result = sqrt(x);
    printf("The square root of %lf is %lf\n", x, result);
    return 0;
}
```

## Сборка

```bash
gcc after.c -o after -lm
./after
```

Ожидаемый вывод:

```
The square root of 0.500000 is 0.707107
```

> **Почему `-lm`?** Стандартная библиотека C разделена на части. `printf` лежит в `libc` (линкуется автоматически), а математические функции (`sqrt`, `sin`, `pow`, ...) — в **`libm`**. Её нужно подключать явно флагом `-l<имя>` (без префикса `lib`).
