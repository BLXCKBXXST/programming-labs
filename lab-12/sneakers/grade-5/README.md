# Lab 12 — sneakers — Оценка 5

## Что реализовано

### Динамический массив через `malloc`

Функции `FillSneakersN`, `BubbleSortByPriceN`, `PrintSneakersN` работают с `Sneaker *` и произвольным `int n` — не привязаны к `#define N`.

### Бенчмарк `gettimeofday`

Измеряет время выполнения сортировки для N = 100, 10 000, 100 000. Показывает квадратичный рост времени O(n²).

```c
struct timeval t1, t2;
gettimeofday(&t1, NULL);
BubbleSortByPriceN(arr, n);
gettimeofday(&t2, NULL);
printf("%.3f мс\n", elapsed_ms(t1, t2));
```

### Структура папок

```
grade-5/
├── src/
│   ├── main.c       — benchmark(100 / 10000 / 100000) + демо сортировки
│   └── sneakers.c   — FillSneakersN, BubbleSortByPriceN, PrintSneakersN
└── include/
    └── sneakers.h   — Sneaker struct, объявления функций
```

## Сборка и запуск

```bash
gcc -Wall -Iinclude src/main.c src/sneakers.c -o sneakers
./sneakers
```
