# Lab 12 — katysha-roguelike — Оценка ★ (+1 балл)

## Что реализовано

Включает всё из оценок 3, 4, 5, плюс:

### Callback-сортировка — `BubbleSortCallback()`

Функция сортировки принимает третьим аргументом **указатель на функцию сравнения** (callback).
Благодаря этому можно сортировать по любому полю без изменения самого алгоритма сортировки.

```c
// прототип callback-функции: принимает два элемента, возвращает > 0 если a > b
void BubbleSortCallback(Room *rooms, int n,
                        int (*cmp)(const Room *, const Room *));

// сортировка по полю level
int CompareByLevel(const Room *a, const Room *b) {
    return a->level - b->level;
}

// сортировка по полю resolution
int CompareByResolution(const Room *a, const Room *b) {
    return a->resolution - b->resolution;
}

// использование:
BubbleSortCallback(arr, 100, CompareByLevel);
BubbleSortCallback(arr, 100, CompareByResolution); // алгоритм не меняется!
```

Так же работает стандартная `qsort()` из `<stdlib.h>`.

## Сборка и запуск

```bash
gcc -Wall -Iinclude -c src/room.c -o room.o
ar rcs libroom.a room.o
gcc -Wall -Iinclude src/main.c libroom.a -o rooms
./rooms
```
