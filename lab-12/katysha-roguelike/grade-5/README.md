# Lab 12 — katysha-roguelike — Оценка 5

## Что реализовано

### Динамический массив через `malloc`

Функции `FillRoomsN`, `BubbleSortByLevelN`, `PrintRoomsN` работают с `Room *` и произвольным `int n`.

### Бенчмарк `gettimeofday`

Измеряет время сортировки по полю `level` для N = 100, 10 000, 100 000. Показывает квадратичный рост времени O(n²).

### Структура папок

```
grade-5/
├── src/
│   ├── main.c   — benchmark(100 / 10000 / 100000) + демо
│   └── room.c   — FillRoomsN, BubbleSortByLevelN, PrintRoomsN
└── include/
    └── room.h   — Room struct, объявления функций
```

## Сборка и запуск

```bash
gcc -Wall -Iinclude src/main.c src/room.c -o rooms
./rooms
```
