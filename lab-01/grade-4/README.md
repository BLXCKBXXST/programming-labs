# Оценка 4 — Цельсий ↔ Фаренгейт

## Задача

Пользователь вводит число и символ единицы: `36.6c` или `98f`. Программа конвертирует в противоположную шкалу. Если символ не `c`/`C`/`f`/`F` — вывести ошибку.

## Формулы

| Из | В | Формула |
|---|---|---|
| °C | °F | `F = C × 9/5 + 32` |
| °F | °C | `C = (F − 32) × 5/9` |

## Код

[temperature.c](temperature.c) — ключевое:

```c
double t;
char unit;
scanf("%lf%c", &t, &unit);   /* читаем число + сразу следующий символ */
unit = tolower((unsigned char)unit);

if (unit == 'c')      printf("Ouput temperature: %.1ff\n", t * 9.0 / 5.0 + 32.0);
else if (unit == 'f') printf("Ouput temperature: %.1fc\n", (t - 32.0) * 5.0 / 9.0);
else                  printf("Ouput error\n");
```

> Регистр единицы игнорируется через `tolower()` — `36.6C` и `36.6c` работают одинаково.

## Сборка

```bash
gcc temperature.c -o temperature
./temperature
```

## Тесты

| Ввод | Вывод |
|---|---|
| `Input temperature: 36.6c` | `Ouput temperature: 97.9f` |
| `Input temperature: 98f`   | `Ouput temperature: 36.7c` |
| `Input temperature: 36.6a` | `Ouput error` |

> Орфография `Ouput` (а не `Output`) — как в эталонном выводе из методички. Сохранена сознательно.
