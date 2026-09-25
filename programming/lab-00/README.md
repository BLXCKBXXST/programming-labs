# Лабораторная №0 — Вывод на экран и типы данных

Знакомство с компилятором, `printf`, форматами вывода и диапазонами числовых типов.

| Задание | Тема | Исходник |
|---|---|---|
| [0](task0/README.md) | Первая программа | [hello.c](task0/hello.c) |
| [1](task1/README.md) | Форматированный вывод | [output.c](task1/output.c) |
| [2](task2/README.md) | Переполнение числовых типов | [overflow.c](task2/overflow.c) |
| [3](task3/README.md) | Символы и коды ASCII | [chars.c](task3/chars.c) |
| [4](task4/README.md) | Исправление ошибок компиляции | [before.c](task4/before.c), [after.c](task4/after.c) |

[PDF задания](Лабораторная%20работа%20№0.pdf)

## Сборка

Из этой папки:

```bash
make all
./task0/hello
./task1/output
./task2/overflow
./task3/chars
./task4/after
make clean
```

Каждое задание также можно собрать отдельно через `make task1` и аналогичные цели.

В `task2` проверяется разница между знаковым и беззнаковым переполнением. `task4/before.c` оставлен с ошибками намеренно; рабочая версия — `task4/after.c`.
