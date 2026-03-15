# Lab 12 — sneakers — Оценка «звёздочка»

## Что реализовано

### BubbleSort через указатель на функцию-компаратор (callback)

`BubbleSortCallback` принимает пользовательскую функцию сравнения — так один алгоритм сортирует по любому полю.

```c
void BubbleSortCallback(Sneaker *s, int n,
                        int(*cmp)(const Sneaker*, const Sneaker*));

// компараторы:
int CompareByPrice(const Sneaker *a, const Sneaker *b) { return a->price - b->price; }
int CompareBySize (const Sneaker *a, const Sneaker *b) { return a->size  - b->size;  }
```

### Бенчмарк `gettimeofday`

Измеряет время выполнения сортировки для N = 100, 10 000, 100 000. Показывает квадратичный рост времени O(n²).

### Структура папок

```
grade-star/
├── src/
│   ├── main.c       — benchmark + демо сортировки
│   └── sneakers.c   — FillSneakersN, BubbleSortCallback, PrintSneakersN
└── include/
    └── sneakers.h   — Sneaker struct, объявления функций
```

## Сборка и запуск

```bash
gcc -Wall -Iinclude src/main.c src/sneakers.c -o sneakers_star
./sneakers_star
```
