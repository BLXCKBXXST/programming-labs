# Оценка 3 — Структура `Fraction` в одном файле

## Задача (вариант 16)

Создать структуру **Дробь** (числитель + знаменатель). Реализовать арифметические действия — **умножение** и **деление**. По требованию PDF: ≥ 2 функции, в которые передаётся структура **или** которые возвращают структуру.

## Идея

```c
typedef struct {
    int a;
    int b;
} Fraction;
```

Все функции работают **по значению**: принимают `Fraction` и возвращают `Fraction`. Это самый простой способ — никаких указателей.

| Функция | Принимает | Возвращает |
|---|---|---|
| `make_fraction(a, b)` | два `int` | `Fraction` |
| `mul_fraction(x, y)`  | две `Fraction` | `Fraction` |
| `div_fraction(x, y)`  | две `Fraction` | `Fraction` |
| `print_fraction(f)`   | `Fraction` | — |

## Код

[fraction.c](fraction.c) — всё в одном файле, без `.h`.

```c
Fraction mul_fraction(Fraction x, Fraction y) {
    Fraction r;
    r.a = x.a * y.a;
    r.b = x.b * y.b;
    return r;
}
```

## Сборка и запуск

```bash
gcc fraction.c -o fraction
./fraction
# Введите дробь 1 (a b): 1 2
# Введите дробь 2 (a b): 3 4
# f1 = 1/2
# f2 = 3/4
# f1 * f2 = 3/8
# f1 / f2 = 4/6
```

> Сокращения дробей нет — `4/6` вместо `2/3`. Не требуется по заданию.
