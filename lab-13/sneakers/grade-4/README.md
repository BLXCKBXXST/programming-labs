# Оценка 4 — CMakeLists.txt

## Что такое CMake?

CMake — это **генератор Makefile-ов**.  
Ты пишешь один `CMakeLists.txt`, а CMake сам создаёт нужные Makefile под твою систему.  
Полезно когда проект большой или нужно собирать на Windows/Linux/Mac.

## Структура

```
grade-4/
├── CMakeLists.txt    # с्крипт сборки для CMake
├── include/
│   └── sneakers.h
└── src/
    ├── main.c
    └── sneakers.c
```

## Как собрать

```bash
# шаг 1: создаём папку для всех генерируемых файлов (cmake не мусорит в исходниках)
mkdir build && cd build

# шаг 2: конфигурируем проект (читает CMakeLists.txt, генерирует Makefile)
cmake ..

# шаг 3: собираем
make

# запуск
./sneakers_app
```

## Сборка с динамической библиотекой

```bash
mkdir build && cd build
cmake .. -DLIB_TYPE=SHARED   # передаём опцию через -D
make
```

## Что значит -DCMAKE_BUILD_TYPE?

Если спросят на экзамене, отвечаешь так:

| Значение | Что делает |
|---|---|
| `Debug` | Включает отладочную информацию, отключает оптимизации. Используешь при разработке. |
| `Release` | Оптимизирует код для скорости. Используешь когда всё готово и нужна скорость. |

```bash
cmake .. -DCMAKE_BUILD_TYPE=Release
```
