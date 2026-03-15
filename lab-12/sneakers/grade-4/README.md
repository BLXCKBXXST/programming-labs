# Lab 12 — sneakers — Оценка 4

## Что реализовано

### Структура папок

```
grade-4/
├── src/
│   ├── main.c       — только main(): заполнить, сортировать, вывести
│   └── sneakers.c   — реализация: FillSneakers, BubbleSortByPrice, PrintSneakers
├── include/
│   └── sneakers.h   — struct Sneaker, #define N 100, объявления функций
└── Makefile
```

### Makefile: цели `all` и `clean`, статическая библиотека

Цепочка сборки:

1. `src/sneakers.c` → `src/sneakers.o`
2. `src/sneakers.o` → `libsneakers.a` (статическая библиотека)
3. `src/main.c` + `libsneakers.a` → `sneakers` (исполняемый файл)

```bash
make        # цель all
./sneakers
make clean  # удаляет .o, .a, sneakers
```
