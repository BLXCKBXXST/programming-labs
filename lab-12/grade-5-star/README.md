# Lab 12 — Grade 5* (под звёздочкой)

Callback для функции сортировки + замер времени.

## Структура
```
grade-5-star/
├── src/
│   ├── main.c
│   └── sneakers.c
└── include/
    └── sneakers.h
```

## Сборка вручную
```bash
gcc -Wall -Iinclude -c src/sneakers.c -o sneakers.o
ar rcs libsneakers.a sneakers.o
gcc -Wall -Iinclude src/main.c libsneakers.a -o sneakers
./sneakers
```

## Что такое callback
Функция `BubbleSortCallback` принимает третьим аргументом **указатель на функцию** сравнения.
Это позволяет сортировать по любому полю не меняя саму функцию сортировки:

```c
// сортировка по цене
BubbleSortCallback(arr, 100, CompareByPrice);

// сортировка по размеру — ничего не меняем в BubbleSort!
BubbleSortCallback(arr, 100, CompareBySize);
```

Так же работает стандартная `qsort()` из `<stdlib.h>`.
