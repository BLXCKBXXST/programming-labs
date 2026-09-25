# Оценка 5 — задание cmake_task

## Что здесь надо сделать

Преподаватель оставил шаблонный проект с **пустыми CMakeLists.txt** и комментариями что дописать.  
Задача — дополнить их чтобы проект собирался.

## Структура проекта

```
grade-5/
├── CMakeLists.txt        # главный: подключает pipes и background
├── src/
│   └── main.c            # использует функции из background
├── background/           # библиотека «фон
│   ├── CMakeLists.txt
│   ├── background.h
│   └── background.c
└── pipes/                # библиотека «трубы»
    ├── CMakeLists.txt
    ├── pipes.h
    ├── read_pipe.c
    └── write_pipe.c
```

## Как работает add_subdirectory

```cmake
add_subdirectory(pipes)       # CMake заходит в папку pipes/ и читает её CMakeLists.txt
add_subdirectory(background)  # то же для background/
```

По сути фолдеры `pipes/` и `background/` — это **отдельные мини-проекты**, каждый со своим CMakeLists.txt.

## Как собрать

```bash
# 1. клонируем ветку с заданием
git clone -b cmake_task https://github.com/kruffka/C-Programming.git cmake_task_original

# 2. изучаем комментарии в CMakeLists.txt и дописываем

# 3. собираем
mkdir build && cd build
cmake ..
make
./cmake_task
```

## Объяснение команд CMake для экзамена

| Команда | Что делает |
|---|---|
| `cmake_minimum_required(VERSION 3.10)` | не запускается на слишком старом cmake |
| `project(name C)` | задаёт имя проекта и язык |
| `add_library(name STATIC file.c)` | создаёт статическую библиотеку |
| `add_executable(name file.c)` | создаёт исполняемый файл |
| `target_link_libraries(app PRIVATE lib)` | подключает библиотеку к приложению |
| `target_include_directories(lib PUBLIC dir)` | указывает папку с .h файлами |
| `add_subdirectory(folder)` | подключает подпроект |
