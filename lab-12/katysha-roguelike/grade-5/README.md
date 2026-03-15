# Lab 12 — katysha-roguelike — Оценка 5

## Что реализовано

Включает всё из оценок 3 и 4, плюс:

### 12–13. Замер времени сортировки — `gettimeofday()`

Используется `gettimeofday()` из `<sys/time.h>` — записывается время до и после сортировки,
разница переводится в миллисекунды:

```c
struct timeval t1, t2;
gettimeofday(&t1, NULL);
BubbleSortByLevelN(arr, n);
gettimeofday(&t2, NULL);
double ms = (t2.tv_sec - t1.tv_sec) * 1000.0 + (t2.tv_usec - t1.tv_usec) / 1000.0;
```

Замер выполняется для трёх значений N:

| N | Ожидаемая сложность |
|--------|------------------|
| 100 | ~0 мс |
| 10 000 | ~100–500 мс |
| 100 000| ~10 000+ мс |

(фактическое значение зависит от машины)

### 14. Динамическая библиотека `.so`

Динамическая библиотека не вставляется в ех файл, а подгружается в память в режиме реального
времени. Несколько процессов могут совместно использовать одну `.so`-библиотеку.

## Сборка и запуск

```bash
# статическая библиотека
gcc -Wall -Iinclude -c src/room.c -o room.o
ar rcs libroom.a room.o

# динамическая библиотека
gcc -Wall -Iinclude -fPIC -shared src/room.c -o libroom.so

# сборка со статической и запуск
gcc -Wall -Iinclude src/main.c libroom.a -o rooms
./rooms
```

> `-fPIC` — флаг Position-Independent Code, необходим для создания `.so`.
