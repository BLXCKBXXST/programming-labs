# Лабораторная работа №12 — Структурирование проекта и библиотеки

![C](https://img.shields.io/badge/C-11-blue) ![Build](https://img.shields.io/badge/build-Makefile-orange) ![Topic](https://img.shields.io/badge/topic-libraries-yellow)

> Вариант 21 — структура **Кроссовки** (бренд, модель, размер, цена). Массив структур, сортировка пузырьком, постепенный переход от одного файла к статической и динамической библиотекам.

## 📊 Прогрессия по оценкам

| Grade | Что нового | Папка |
|---|---|---|
| 3 ★   | Структура `Sneaker` + массив + сортировка пузырьком — всё в одном `main.c` | [grade-3](grade-3) |
| 4 ★★  | Разделение на `main.c` + `sneakers.c/h` + сборка через **статическую** библиотеку `libsneakers.a` | [grade-4](grade-4) |
| 5 ★★★ | + **динамическая** библиотека `libsneakers.so` + замер времени для N=100/10 000/100 000 | [grade-5](grade-5) |
| ★     | callback для функции сортировки (можно сортировать по цене, бренду, размеру) | [grade-star](grade-star) |

## 🗂 Структура

```
lab-12/
├── README.md
├── Makefile                       # диспетчер: make all / grade-N / clean
├── Лабораторная работа №12.pdf
├── grade-3/
│   ├── main.c
│   └── README.md
├── grade-4/
│   ├── include/sneakers.h
│   ├── src/{main.c, sneakers.c}
│   └── README.md
├── grade-5/
│   ├── include/sneakers.h
│   ├── src/{main.c, sneakers.c}
│   └── README.md
└── grade-star/
    ├── include/sneakers.h
    ├── src/{main.c, sneakers.c}
    └── README.md
```

## ⚙️ Сборка и запуск

```bash
make all              # собрать все четыре
make grade-3          # только grade-3
./grade-3/sneakers
./grade-4/sneakers
./grade-5/sneakers    # запустит замер времени
./grade-star/sneakers
make clean
```

## 📸 Скриншоты

| Что | Где |
|---|---|
| Таблица **до** и **после** сортировки пузырьком (grade-3) | ![sort](grade-3/sort.png) |
| Замер времени **STATIC vs SHARED** для N = 100 / 10 000 / 100 000 (grade-5) | ![bench](grade-5/benchmark.png) |

## 🧠 Что отрабатывается

- **Многофайловые проекты**: каждая функция — в своём `.c`, заголовок один на всех.
- **Сборка библиотек**: статическая (`ar rcs`) vs динамическая (`gcc -shared`).
- **Профилирование**: `gettimeofday` / `clock_gettime` для миллисекундных замеров.
- **Сортировки**: пузырёк, его O(n²), почему он плох на больших данных.
- **Callback-функции** (★): как сделать сортировку конфигурируемой.
