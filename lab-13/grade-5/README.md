# Lab 13 — Grade 5

## Сборка через Make
```bash
make
./sneakers
make clean
```

## Сборка через CMake
```bash
mkdir build && cd build

# Debug сборка (с отладочными символами, без оптимизации)
cmake -DCMAKE_BUILD_TYPE=Debug -DLIB_TYPE=STATIC ..

# Release сборка (с оптимизацией -O3)
cmake -DCMAKE_BUILD_TYPE=Release -DLIB_TYPE=SHARED ..

cmake --build .
./sneakers
```

## Объяснение -DCMAKE_BUILD_TYPE
| Значение | Флаги компилятора | Назначение |
|----------|------------------|------------|
| `Debug`   | `-g -O0`         | Отладка с gdb, медленно |
| `Release` | `-O3 -DNDEBUG`   | Продакшн, быстро |

## Задание на оценку 5
Склонировать ветку `cmake_task`:
```bash
git clone -b cmake_task https://github.com/kruffka/C-Programming.git
cd C-Programming
# Дописать CMakeLists.txt согласно комментариям
```
