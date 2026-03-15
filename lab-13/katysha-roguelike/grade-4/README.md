# Lab 13 — katysha-roguelike — Оценка 4

## Что реализовано

Включает всё из оценки 3, плюс:

### 5–6. CMakeLists.txt

CMake-файл описывает сборку библиотеки `room` и исполняемого `rooms`.

```cmake
cmake_minimum_required(VERSION 3.10)
project(roguelike_lab13 C)
set(CMAKE_C_STANDARD 99)
set(LIB_TYPE "STATIC" CACHE STRING "Library type: STATIC or SHARED")
add_library(room ${LIB_TYPE} src/room.c)
target_include_directories(room PUBLIC include)
add_executable(rooms src/main.c)
target_link_libraries(rooms PRIVATE room)
```

### 7. Выбор типа библиотеки через `-D`

```bash
# статическая библиотека (по умолчанию)
cmake -B build -DLIB_TYPE=STATIC

# динамическая библиотека
cmake -B build -DLIB_TYPE=SHARED
```

### 8. `-DCMAKE_BUILD_TYPE`

| Значение | Что делает |
|---|---|
| `Debug` | без оптимизации (`-O0`), с отладочной информацией (`-g`) |
| `Release` | с оптимизацией (`-O2`/`-O3`), без отладочной информации |

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake -B build -DCMAKE_BUILD_TYPE=Release
```

## Сборка и запуск

```bash
cmake -B build -DLIB_TYPE=STATIC -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/rooms
```
