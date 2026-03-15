# Lab 12 — katysha-roguelike — Оценка 4

## Что реализовано

### Структура папок

```
grade-4/
├── src/
│   ├── main.c    — только main(): заполнить, сортировать, вывести
│   └── room.c    — реализация: FillRooms, BubbleSortByLevel, PrintRooms
├── include/
│   └── room.h    — struct Room, #define N 100, объявления функций
└── Makefile
```

### Makefile: цели `all` и `clean`, статическая библиотека

Цепочка сборки:
1. `src/room.c` → `src/room.o`
2. `src/room.o` → `libroom.a`
3. `src/main.c` + `libroom.a` → `rooms`

```bash
make        # цель all
./rooms
make clean  # удаляет .o, .a, rooms
```
