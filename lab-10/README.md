# Лабораторная работа №10 — Структуры данных

![C](https://img.shields.io/badge/C-11-blue) ![Build](https://img.shields.io/badge/build-Makefile-orange) ![Topic](https://img.shields.io/badge/topic-structs%20%2B%20malloc-yellow)

> Вариант 16 — структура **Дробь** (числитель + знаменатель), функции умножения и деления. Реализована на четырёх уровнях сложности по PDF.

## 📊 Прогрессия по оценкам

| Grade | Что нового по сравнению с предыдущей | Файлы |
|---|---|---|
| 3 ★   | Структура + ≥ 2 функции, всё в одном файле | [grade-3](grade-3) |
| 4 ★★  | Разбивка на 3 файла: main.c / fraction.c / fraction.h | [grade-4](grade-4) |
| 5 ★★★ | Указатели на структуру + массив через `malloc` | [grade-5](grade-5) |
| ★     | Отдельный Makefile с компиляцией через `.o` объектники | [grade-star](grade-star) |

## 🗂 Структура

```
lab-10/
├── README.md
├── Makefile                       # диспетчер: make all / grade-N / clean
├── Лабораторная работа №10.pdf
├── grade-3/
│   ├── fraction.c                 # всё в одном файле
│   └── README.md
├── grade-4/
│   ├── main.c, fraction.c, fraction.h
│   └── README.md
├── grade-5/
│   ├── main.c, fraction.c, fraction.h    # с указателями
│   └── README.md
└── grade-star/
    ├── Makefile                   # компиляция через .o
    └── README.md
```

## ⚙️ Сборка

```bash
make all              # собрать все четыре варианта
make grade-3          # только grade-3
make grade-4
make grade-5
make grade-star
make clean
```

Или вручную в нужной папке:

```bash
gcc grade-3/fraction.c -o grade-3/fraction
gcc grade-4/main.c grade-4/fraction.c -o grade-4/fraction
gcc grade-5/main.c grade-5/fraction.c -o grade-5/fraction_dyn
make -C grade-star
```

## 🧠 Что отрабатывается

- **Структуры**: `typedef struct { int a; int b; } Fraction;`.
- **Функции структур**: передача по значению (grade-3, grade-4) vs передача по указателю (grade-5).
- **Многофайловые проекты**: header `.h` с прототипами, исходники `.c` с реализацией.
- **Динамическая память**: `malloc / free`, массив переменной длины.
- **Makefile**: правила, переменные, автоматические `$@ $< $^`, разделение на компиляцию и линковку.
