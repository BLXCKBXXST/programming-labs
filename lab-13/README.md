# Лабораторная работа №13 — Системы сборки Make и CMake

![C](https://img.shields.io/badge/C-11-blue) ![Make](https://img.shields.io/badge/build-Make-orange) ![CMake](https://img.shields.io/badge/build-CMake-blueviolet) ![Topic](https://img.shields.io/badge/topic-build%20systems-yellow)

> Та же тема «Кроссовки» из [lab-12](../lab-12), но теперь упор на **автоматизацию сборки**. По мере роста grade меняется и инструмент.

## 📊 Прогрессия по оценкам

| Grade | Что нового | Инструмент | Папка |
|---|---|---|---|
| 3 ★   | Makefile с целями `all`, `clean`, сборка статической библиотеки | **Make** | [grade-3](grade-3) |
| 4 ★★  | CMakeLists.txt + опция `-DLIB_TYPE=STATIC/SHARED` + `CMAKE_BUILD_TYPE` | **CMake** | [grade-4](grade-4) |
| 5 ★★★ | Многомодульный проект с подпроектами `pipes/` и `background/` (через `add_subdirectory`) | **CMake** | [grade-5](grade-5) |

> Смешение Make и CMake в одной лабе — это **по заданию**. На grade 3 — учим Make, на 4–5 переходим на CMake чтобы понять, чем он удобнее на крупных проектах.

## 🗂 Структура

```
lab-13/
├── README.md
├── Makefile                       # диспетчер: вызывает Make для grade-3 и CMake для 4/5
├── Лабораторная работа №13.pdf
├── grade-3/
│   ├── Makefile
│   ├── include/sneakers.h
│   ├── src/{main.c, sneakers.c}
│   └── README.md
├── grade-4/
│   ├── CMakeLists.txt
│   ├── include/, src/
│   └── README.md
└── grade-5/
    ├── CMakeLists.txt
    ├── src/main.c
    ├── pipes/{pipes.h, read_pipe.c, write_pipe.c, CMakeLists.txt}
    ├── background/{background.h, background.c, CMakeLists.txt}
    └── README.md
```

## 📥 Установка зависимостей

```bash
sudo apt install build-essential cmake -y
```

## ⚙️ Сборка

```bash
make all                     # собрать всё (Make для 3, CMake для 4/5)

make grade-3                 # делегирует в grade-3/Makefile
make grade-4                 # cmake -S grade-4 -B grade-4/build && cmake --build
make grade-5

make clean                   # подчищает Make-объекты и CMake build-папки
```

Можно собирать каждый grade напрямую:

```bash
# grade-3 (Make)
cd grade-3 && make && ./sneakers

# grade-4 (CMake, статическая)
cd grade-4
cmake -S . -B build -DLIB_TYPE=STATIC && cmake --build build
./build/sneakers

# grade-4 (CMake, динамическая)
cmake -S . -B build -DLIB_TYPE=SHARED && cmake --build build
LD_LIBRARY_PATH=./build ./build/sneakers

# grade-5 (CMake с подпроектами)
cd grade-5
cmake -S . -B build && cmake --build build
./build/sneakers
```

## 📸 Скриншоты

| Что | Где |
|---|---|
| Вывод `make` в grade-3 (компиляция + линковка) | ![make](grade-3/make.png) |
| Вывод `cmake --build` для grade-4 (со статической или динамической библиотекой) | ![cmake-4](grade-4/cmake.png) |
| Вывод `cmake --build` для grade-5 (с подпроектами `pipes/` и `background/`) | ![cmake-5](grade-5/cmake.png) |

## 🧠 Что отрабатывается

| Концепция | Где |
|---|---|
| Цели, переменные, автоматические `$@ $< $^`, `.PHONY` | grade-3 |
| `add_library(... STATIC/SHARED ...)`, `target_link_libraries`, `target_include_directories` | grade-4 |
| `option(...)` для выбора параметров сборки | grade-4 |
| `CMAKE_BUILD_TYPE = Debug / Release` и как это влияет на флаги | grade-4 |
| `add_subdirectory()` — подпроекты как отдельные модули | grade-5 |
| Конвенция «out-of-source build» (отдельная папка `build/`) | grade-4, 5 |
