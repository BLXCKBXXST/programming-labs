# Lab 13 — katysha-roguelike — Оценка 5

## Что реализовано

### 9–11. Многомодульный CMake (несколько библиотек)

Проект разбит на несколько библиотек через `add_subdirectory`.

### Структура папок

```
grade-5/
├── CMakeLists.txt      — корневой файл: add_subdirectory + add_executable
├── src/
│   └── main.c             — использует background-библиотеку
├── pipes/
│   └── CMakeLists.txt     — add_library(pipes ...) — библиотека pipes
└── background/
    └── CMakeLists.txt     — add_library(background ...) — зависит от pipes
```

### Цепочка зависимостей

```
pipes ← background ← cmake_task
```

### `add_subdirectory` в действии

```cmake
add_subdirectory(pipes)       # собирает библиотеку pipes
add_subdirectory(background)  # собирает библиотеку background
add_executable(cmake_task src/main.c)
target_link_libraries(cmake_task PRIVATE background)
```

## Сборка и запуск

```bash
cmake -B build
cmake --build build
./build/cmake_task
```
