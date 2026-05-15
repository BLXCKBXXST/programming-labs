# Лабораторная работа №16 — POSIX потоки (pthread)

![C](https://img.shields.io/badge/C-11-blue) ![pthread](https://img.shields.io/badge/lib-pthread-green) ![Plot](https://img.shields.io/badge/plot-matplotlib-orange)

> 10 упражнений на знакомство с POSIX threads + задача обедающих философов под звёздочку. По PDF — «Практическое задание 6. Знакомство с POSIX потоками».

## 📊 Привязка к оценкам

| Grade | Упражнения | Папка |
|---|---|---|
| 3 ★   | 1–6: create / join / args / cancel / cleanup / sleepsort | [grade-3](grade-3) |
| 4 ★★  | 7–9: mutex-синхронизация вывода, перемножение матриц с распараллеливанием, замер времени и **график** | [grade-4](grade-4) |
| 5 ★★★ | 10: блокирующая FIFO-очередь сообщений + односторонний чат с N клиентами / M серверами | [grade-5](grade-5) |
| ★     | обедающие философы — дедлок и его устранение асимметричным захватом | [grade-star](grade-star) |

Кроме исходников и Makefile, есть **[threads.md](threads.md)** — обзорный отчёт со скриншотами / графиком (его требует PDF).

## 🗂 Структура

```
lab-16/
├── README.md
├── threads.md
├── Лабораторная работа №16.pdf
├── grade-3/
│   ├── ex1_create.c .. ex6_sleepsort.c
│   ├── Makefile
│   └── README.md
├── grade-4/
│   ├── ex7_sync.c, ex8_matmul.c, ex9_benchmark.c
│   ├── benchmark.py / benchmark.csv / benchmark.png
│   ├── Makefile
│   └── README.md
├── grade-5/
│   ├── msgqueue.{h,c}, chat.c
│   ├── Makefile
│   └── README.md
└── grade-star/
    ├── din_phil.c           # оригинал (deadlock)
    ├── din_phil_fixed.c     # асимметричный захват — нет дедлока
    ├── Makefile
    └── README.md
```

## 📥 Зависимости

```bash
sudo apt install -y build-essential python3-matplotlib
```

## ⚙️ Полная сборка и быстрая проверка

```bash
# grade-3 — 6 упражнений
(cd grade-3 && make && for f in ex*; do test -x "$f" && echo "=== $f ===" && ./$f; done)

# grade-4 — матричные тесты + бенчмарк
(cd grade-4 && make && ./ex7_sync && ./ex8_matmul 3 2 && python3 benchmark.py)

# grade-5 — чат на 5 секунд
(cd grade-5 && make && ./chat)

# звёздочка
(cd grade-star && make && ./din_phil_fixed)
```

## 🔗 Полезные ссылки

- PDF задания: [Лабораторная работа №16.pdf](Лабораторная%20работа%20№16.pdf)
- Оригинал философов: <https://github.com/kruffka/C-Programming/blob/2025-2026/16_threads/src/din_phil.c>
- Отчёт с разбором результатов: [threads.md](threads.md)
