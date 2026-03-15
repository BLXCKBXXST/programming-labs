# Lab 13 — Grade 4

Содержит CMakeLists.txt + структуру src/ / include/ + выбор типа библиотеки через `-DLIB_TYPE`.

## Сборка
```bash
cmake -B build -DLIB_TYPE=STATIC   # или SHARED, папка build создастся автоматически
cmake --build build
./build/sneakers
```

## Опция -DCMAKE_BUILD_TYPE

`-DCMAKE_BUILD_TYPE` управляет режимом сборки и определяет, какие флаги передаются компилятору.

### Debug
- Флаги: `-g -O0`
- `-g` — включает отладочные символы в бинарник, без них `gdb` не сможет показать строки кода
- `-O0` — отключает оптимизацию, код выполняется точно так, как написан
- Бинарник больше и медленнее, но удобен для отладки

### Release
- Флаги: `-O3 -DNDEBUG`
- `-O3` — максимальная оптимизация: инлайнинг, развёртывание циклов, код работает быстрее
- `-DNDEBUG` — отключает все `assert()`, проверки не выполняются в продакшне
- Бинарник меньше и быстрее, но отладка через `gdb` невозможна

### Пример
```bash
# Отладка
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
gdb ./build/sneakers

# Продакшн
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/sneakers
```
