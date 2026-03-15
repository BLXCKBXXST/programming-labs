# Lab 12 — sneakers — Оценка 4

## Что реализовано

Включает всё из оценки 3, плюс:

### 8. Разбивка на 3 файла

```
include/sneakers.h  — заголовочный: тип Sneaker, объявления функций
src/sneakers.c     — исходный: реализации FillSneakers, BubbleSortByPrice, PrintSneakers
src/main.c         — исходный: только main()
```

### 9. Статическая библиотека `.a`

Статическая библиотека — это архив скомпилированных объектных файлов (`.o`).
При линковке код библиотеки вставляется прямо в исполняемый файл.

### 10. Линковка и запуск

```bash
# 1. компиляция sneakers.c в объектный файл
gcc -Wall -Iinclude -c src/sneakers.c -o sneakers.o

# 2. сборка статической библиотеки
ar rcs libsneakers.a sneakers.o

# 3. линковка main.c с библиотекой и запуск
gcc -Wall -Iinclude src/main.c libsneakers.a -o sneakers
./sneakers
```

> `ar rcs` — утилита архивации. `r` — добавить/заменить файл, `c` — создать архив, `s` — индекс символов.
