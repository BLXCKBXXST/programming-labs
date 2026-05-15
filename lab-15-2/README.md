# Лабораторная работа №15.2 — Отладка (debug_task)

![C](https://img.shields.io/badge/C-11-blue) ![Build](https://img.shields.io/badge/build-Makefile-orange) ![Topic](https://img.shields.io/badge/topic-debugging-red)

> Дополнительное задание: найти и исправить баги в 5 учебных программах + одна под звёздочку.
> Источник: ветка [`debug_task`](https://github.com/kruffka/C-Programming/tree/debug_task) репозитория `kruffka/C-Programming`.

## 📊 Привязка к оценкам

| Grade | Задания |
|---|---|
| 3 ★   | любые **2 из** task1–task4 |
| 4 ★★  | **все** task1–task4 |
| 5 ★★★ | + task5 (криптография) |
| ★     | task_star (4G/5G симулятор — программа должна пройти под ASan + UBSan без замечаний) |

## ⚠️ Пересечение с lab-11

Файлы **task1–task4** содержат ровно те же баги, что в [lab-11](../lab-11) (а PDF [lab-11](../lab-11/Лабораторная%20работа%20№11.pdf) — это, по сути, выборка из `debug_task`). Здесь они приведены в полном виде для самодостаточности папки. Если делаешь сдачу — достаточно одной из лаб.

| Файл | Класс ошибки | Подробности |
|---|---|---|
| [src/task1.c](src/task1.c) | передача указателя по значению → SIGSEGV | [lab-11/task-1](../lab-11/task-1/README.md) |
| [src/task2.c](src/task2.c) | `sprintf` overflow в `char str[4]`, затирание соседнего поля | [lab-11/task-2](../lab-11/task-2/README.md) |
| [src/task3.c](src/task3.c) | макрос без скобок: `SQR(y+1)` = 11 | [lab-11/task-3](../lab-11/task-3/README.md) |
| [src/task4.c](src/task4.c) | двойной своп при транспонировании | [lab-11/task-4](../lab-11/task-4/README.md) |
| [src/task5.c](src/task5.c) | **новое**: 6 багов в крипто-алгоритмах (off-by-one, sizeof vs strlen) | см. ниже |
| [src/task_star.c](src/task_star.c) | **новое, ★**: 10+ багов в симуляторе 4G/5G | см. [DEBUG_LOG.md](DEBUG_LOG.md) |

## 🔍 task5 — криптография

Фрагменты с найденными багами:

1. `xor_encrypt` — цикл `i <= text_len` (off-by-one), терминатор не ставится.
2. `caesar_cipher` — условие `> 'a' && < 'z'` пропускает крайние буквы, отрицательный shift даёт отрицательный `%`.
3. `vigenere_encrypt` — ключ в верхнем регистре, а нормализация шла к `'a'`. Плюс сложение без модуля 26.
4. `simple_rc4` — цикл `i < 256 + 32` обращается к `S[256..287]`, off-by-one во внутреннем цикле.
5. `simple_hash` — `sizeof(str)` это размер указателя (8 байт), не длина строки.
6. `generate_key` — i ≤ length пишет за границу буфера, нет терминатора.

## 🌐 task_star — симулятор 4G/5G сети

Содержит **10+ намеренных багов** разных классов: off-by-one в массивах, неинициализированные переменные, рекурсия без терминатора, use-after-return, double free, stack-buffer-overflow. Подробный разбор каждого — в [DEBUG_LOG.md](DEBUG_LOG.md). После исправлений программа должна пройти с `-fsanitize=address,undefined` без единого замечания.

## ⚙️ Сборка и запуск

В Makefile зашит флаг `-fsanitize=address,undefined` — каждая программа сразу проверяется санитайзерами. Если был бы баг — ASan напечатал бы подробный отчёт с указанием строки.

```bash
make all                       # собрать все 6
./src/task1                    # каждый по очереди
./src/task2
./src/task3
./src/task4
./src/task5
./src/task_star
make clean
```

Все программы должны отработать **без падений и без жалоб санитайзеров**.

## 🛠 Полезные команды отладки

| Команда | Что делает |
|---|---|
| `gcc -g -fsanitize=address task.c -o t && ./t` | AddressSanitizer — out-of-bounds, use-after-free, double-free |
| `gcc -g -fsanitize=undefined task.c -o t && ./t` | UBSan — переполнения, неинициализированные, signed UB |
| `valgrind --leak-check=full ./t` | подробная карта обращений к памяти |
| `gdb ./t` → `run` → `bt` | пошаговая отладка, бэктрейс при крэше |
| `cpp -E task.c \| less` | посмотреть результат препроцессора (для макросов) |
