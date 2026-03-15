# Lab 13 — sneakers — Оценка 3

## Что реализовано

### Структура папок

```
grade-3/
├── src/
│   ├── main.c        — только main()
│   └── sneakers.c    — FillSneakers, BubbleSortByPrice, PrintSneakers
├── include/
│   └── sneakers.h    — struct Sneaker, #define N, объявления
└── Makefile
```

### Makefile: цепочка сборки

1. `src/sneakers.c` → `src/sneakers.o`
2. `src/sneakers.o` → `libsneakers.a` (статическая библиотека)
3. `src/main.c` + `libsneakers.a` → `sneakers`

```bash
make        # цель all
./sneakers
make clean  # удаляет .o, .a, sneakers
```
