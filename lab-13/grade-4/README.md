# Lab 13 — Grade 4

Содержит CMakeLists.txt + структуру src/ / include/.

## Сборка
```bash
mkdir build && cd build
cmake -DLIB_TYPE=STATIC ..   # или SHARED
cmake --build .
./sneakers
```

## -DCMAKE_BUILD_TYPE
- `Debug`   — флаги `-g -O0`, удобно для отладки через gdb
- `Release` — флаги `-O3 -DNDEBUG`, оптимизированная сборка
