# Lab 13 — sneakers — Оценка 4

## Что реализовано

Включает всё из оценки 3, плюс CMakeLists.txt.

### CMakeLists.txt

```cmake
set(LIB_TYPE "STATIC" CACHE STRING "Library type: STATIC or SHARED")
add_library(sneakers ${LIB_TYPE} src/sneakers.c)
target_include_directories(sneakers PUBLIC include)
add_executable(sneakers_app src/main.c)
target_link_libraries(sneakers_app PRIVATE sneakers)
```

### Выбор типа библиотеки через `-DLIB_TYPE`

```bash
# статическая библиотека (по умолчанию)
cmake -B build -DLIB_TYPE=STATIC

# динамическая библиотека
cmake -B build -DLIB_TYPE=SHARED
```

### `-DCMAKE_BUILD_TYPE`

| Значение | Что делает |
|---|---|
| `Debug` | `-O0 -g` — без оптимизации, с отладочными символами |
| `Release` | `-O2`/`-O3` — оптимизированная сборка |

## Сборка и запуск

```bash
cmake -B build -DLIB_TYPE=STATIC -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/sneakers_app
```
