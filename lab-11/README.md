# Лабораторная работа №11 — Отладка

![C](https://img.shields.io/badge/C-11-blue) ![Build](https://img.shields.io/badge/build-Makefile-orange) ![Topic](https://img.shields.io/badge/topic-debugging-red)

> Четыре задачи с разными классами ошибок: segfault, buffer overflow, неправильный макрос, двойной своп. Цель — **найти, объяснить и исправить**.

## 🗂 Структура

```
lab-11/
├── Makefile
├── task-1/                # segfault (init по значению)
│   ├── before.c           # код с багом из методички
│   ├── after.c            # исправленный
│   └── README.md          # разбор причины и фикса
├── task-2/                # buffer overflow (sprintf в str[4])
│   ├── before.c
│   ├── after.c
│   └── README.md
├── task-3/                # макрос без скобок
│   ├── before.c
│   ├── after.c
│   └── README.md
├── task-4/                # двойной своп при транспонировании
│   ├── before.c
│   ├── after.c
│   └── README.md
└── README.md
```

## 🐛 Классы ошибок

| № | Класс ошибки | Симптом | Где разбор |
|---|---|---|---|
| 1 | Передача указателя по значению | `SIGSEGV` при чтении NULL | [task-1/README.md](task-1/README.md) |
| 2 | Buffer overflow → затирание соседнего поля | `num` меняется сам собой | [task-2/README.md](task-2/README.md) |
| 3 | Макрос без скобок → неправильный приоритет | `SQR(y+1) = 11` вместо 36 | [task-3/README.md](task-3/README.md) |
| 4 | Двойной обмен в цикле `i,j ∈ [0..N)` | Матрица не меняется | [task-4/README.md](task-4/README.md) |

## ⚙️ Сборка

```bash
make                  # собрать только after-версии (фиксы)
make clean
```

> `before.c` намеренно НЕ собираются автоматически — это «грязный» код. Если хочешь убедиться, что баг есть:
>
> ```bash
> gcc task-1/before.c -o /tmp/t1_bad
> ./tmp/t1_bad           # упадёт с Segmentation fault
> ```

## 🛠 Полезные инструменты для отладки

| Инструмент | Что ловит | Команда |
|---|---|---|
| **AddressSanitizer** | переполнения буфера, use-after-free, утечки | `gcc -fsanitize=address -g task.c -o t && ./t` |
| **UndefinedBehaviorSanitizer** | целочисленные переполнения, недостижимый код | `gcc -fsanitize=undefined -g task.c -o t && ./t` |
| **Valgrind** | утечки памяти, обращения к неинициализированному | `valgrind --leak-check=full ./t` |
| **gdb** | пошаговое выполнение, watchpoints | `gcc -g task.c -o t && gdb ./t` |

> Для задач 1 и 2 особенно эффективен AddressSanitizer — он печатает точную строку, где произошло обращение за границу.
