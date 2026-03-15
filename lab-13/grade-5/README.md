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
cmake -DLIB_TYPE=STATIC ..   # или SHARED
cmake --build .
./sneakers
```

## Задание на оценку 5
Склонировать ветку `cmake_task` и дописать CMakeLists.txt согласно комментариям:
```bash
git clone -b cmake_task https://github.com/kruffka/C-Programming.git
cd C-Programming
# Дописать CMakeLists.txt согласно комментариям в шаблоне
```
