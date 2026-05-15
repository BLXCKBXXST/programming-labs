# Оценка 3 — Makefile + статическая библиотека

## Структура проекта

```
grade-3/
├── Makefile          # сценарий сборки
├── include/
│   └── sneakers.h    # заголовочный файл
└── src/
    ├── main.c        # только main()
    └── sneakers.c    # реализация функций
```

## Что такое Makefile и зачем он нужен?

Без Makefile нужно каждый раз вручную писать длинные команды:  
```bash
gcc -Wall -I include -c src/sneakers.c -o src/sneakers.o
ar rcs libsneakers.a src/sneakers.o
gcc -Wall -I include src/main.c libsneakers.a -o sneakers
```
С Makefile достаточно написать **`make`** — и всё выполнится автоматически.

## Как работает Makefile

Makefile состоит из **целей** (правил). Формат каждой цели:

```
цель: зависимости
<TAB> команда
```

> ⚠УЧТИ: перед командой обязательно **TAB** (не пробелы!), иначе make выдаст ошибку.

## Магические переменные

| Переменная | Что означает |
|---|---|
| `$@` | цель (.то, что слева от `:`) |
| `$<` | первая зависимость |
| `$^` | все зависимости списком |

## Как собрать и запустить

```bash
make          # собрать всё
./sneakers    # запустить
make clean    # удалить скомпилированные файлы
```

## Что создаёт make

```
gcc -Wall -I include -c src/sneakers.c -o src/sneakers.o   ← объектный файл
ar rcs libsneakers.a src/sneakers.o                        ← статическая библиотека
gcc -Wall -I include src/main.c libsneakers.a -o sneakers   ← исполняемый файл
```
