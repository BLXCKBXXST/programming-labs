# Lab 12 — katysha-roguelike — Оценка «звёздочка»

## Что реализовано

### BubbleSort через указатель на функцию-компаратор (callback)

`BubbleSortCallback` принимает пользовательскую функцию сравнения — так один алгоритм сортирует по любому полю.

```c
void BubbleSortCallback(Room *r, int n,
                        int(*cmp)(const Room*, const Room*));

// компараторы:
int CompareByLevel     (const Room *a, const Room *b) { return a->level      - b->level;      }
int CompareByResolution(const Room *a, const Room *b) { return a->resolution - b->resolution; }
```

### Бенчмарк `gettimeofday`

Измеряет время сортировки для N = 100, 10 000, 100 000. Показывает квадратичный рост O(n²).

### Структура папок

```
grade-star/
├── src/
│   ├── main.c   — CompareByLevel, CompareByResolution, benchmark
│   └── room.c   — FillRoomsN, BubbleSortCallback, PrintRoomsN
└── include/
    └── room.h   — Room struct, объявления функций
```

## Сборка и запуск

```bash
gcc -Wall -Iinclude src/main.c src/room.c -o rooms_star
./rooms_star
```
