# Lab 12 — sneakers — Оценка ★ (+1 балл)

## Что реализовано

Включает всё из оценок 3, 4, 5, плюс:

### Callback-сортировка — `BubbleSortCallback()`

Функция сортировки принимает третьим аргументом **указатель на функцию сравнения** (callback).
Благодаря этому можно сортировать по любому полю без изменения самого алгоритма сортировки.

```c
// прототип callback-функции: принимает два элемента, возвращает > 0 если a > b
void BubbleSortCallback(Sneaker *sneakers, int n,
                        int (*cmp)(const Sneaker *, const Sneaker *));

// сортировка по цене
int CompareByPrice(const Sneaker *a, const Sneaker *b) {
    return a->price - b->price;
}

// сортировка по размеру
int CompareBySize(const Sneaker *a, const Sneaker *b) {
    return a->size - b->size;
}

// использование:
BubbleSortCallback(arr, 100, CompareByPrice);
BubbleSortCallback(arr, 100, CompareBySize); // алгоритм не меняется!
```

Так же работает стандартная `qsort()` из `<stdlib.h>`.

## Сборка и запуск

```bash
gcc -Wall -Iinclude -c src/sneakers.c -o sneakers.o
ar rcs libsneakers.a sneakers.o
gcc -Wall -Iinclude src/main.c libsneakers.a -o sneakers
./sneakers
```
