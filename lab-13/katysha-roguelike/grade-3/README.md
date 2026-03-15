# Lab 13 — katysha-roguelike — Оценка 3

## Что реализовано

### 1. Структура папок

Код из лабы 12 разбит по каталогам:

```
grade-3/
├── src/
│   ├── main.c     — только main()
│   └── room.c     — реализации: FillRooms, BubbleSortByLevel, PrintRooms
├── include/
│   └── room.h     — struct Room, #define N, объявления функций
└── Makefile
```

### 2–4. Makefile с целями `all` и `clean`

Цепочка сборки:
1. `src/room.c` → `src/room.o`
2. `src/room.o` → `libroom.a` (статическая библиотека)
3. `src/main.c` + `libroom.a` → `rooms` (исполняемый файл)

```bash
make        # цель all
./rooms
make clean  # удаляет .o, .a и rooms
```
