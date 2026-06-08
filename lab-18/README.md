# Лабораторная работа №18 — Paint++ на C++ с SFML

![C++](https://img.shields.io/badge/C++-17-blue) ![SFML](https://img.shields.io/badge/library-SFML%202.5-green) ![Build](https://img.shields.io/badge/build-CMake-orange)

> Реализация простого графического редактора на базе библиотеки SFML. Задача — дополнить недостающие функции рисования, освоив базовые конструкции C++, алгоритмы и контейнеры STL.

## 📦 Используемая библиотека

[SFML](https://www.sfml-dev.org/) — Simple and Fast Multimedia Library. Предоставляет окно, события мыши/клавиатуры и примитивы для 2D-рендеринга.

Установка:

```bash
# Ubuntu/Debian
sudo apt install libsfml-dev cmake
```

## 📊 Привязка к оценкам

| Grade | Что реализовано | Файл |
|---|---|---|
| 3 ★   | `clearCanvas`, `drawPixel`, `drawBrush`, `drawRectangle` | [grade-3/src/paint_core.cpp](grade-3/src/paint_core.cpp) |
| 4 ★★  | + `drawLine` (Брезенхем), `undo`, изменение кисти, выбор цвета | — |
| 5 ★★★ | + `applyGrayscale`, `applyNegative`, `applyBlur`, клавиши G/N/M | — |

## 🗂 Структура

```
lab-18/
├── README.md
├── CMakeLists.txt              # корневая сборка
└── grade-3/
    ├── CMakeLists.txt          # сборка grade-3
    ├── README.md               # описание реализованного
    └── src/
        ├── paint_core.hpp      # объявления констант и функций
        ├── paint_core.cpp      # реализация функций рисования
        └── main.cpp            # основной цикл, обработка событий
```

## ⚙️ Сборка и запуск

```bash
cd grade-3
mkdir build && cd build
cmake ..
make
./paint
```

### Запуск графики в WSL

WSL 2 с WSLg — графика работает автоматически. Для WSL 2 с внешним X-сервером (VcXsrv):

```bash
export DISPLAY=$(cat /etc/resolv.conf | grep nameserver | awk '{print $2}'):0
```

## 🎨 Управление

| Клавиша | Действие |
|---|---|
| `B` | Кисть (круг) |
| `R` | Прямоугольник |
| `L` | Линия |
| `E` | Ластик |
| `C` | Очистить холст |
| `Ctrl+Z` | Отмена (undo) |
| `0`–`9` | Выбор цвета из палитры |
| `+` / `-` | Размер кисти |

## 🧠 Что отрабатывается

- Работа с **двумерным `std::vector`** как холстом (`Canvas = vector<vector<sf::Color>>`).
- Алгоритмы STL: **`std::fill`**, **`std::transform`**, **`std::min`/`std::max`**.
- Обработка **событий мыши и клавиатуры** через `sf::Event`.
- Алгоритм **Брезенхема** для рисования отрезка по пикселям.
- Паттерн **undo** через `std::stack`.
- Фильтры изображений: оттенки серого, негатив, размытие 3×3.
