# Lab 13 — Grade 5

Проект на основе задания [kruffka/C-Programming (cmake_task)](https://github.com/kruffka/C-Programming/tree/cmake_task).

## Структура
```
grade-5/
├── CMakeLists.txt        ← корневой: add_subdirectory + add_executable
├── src/
│   └── main.c
├── pipes/
│   ├── CMakeLists.txt    ← библиотека pipes
│   ├── pipes.h
│   ├── read_pipe.c
│   └── write_pipe.c
└── background/
    ├── CMakeLists.txt    ← библиотека background, линкуется с pipes
    ├── background.h
    └── background.c
```

## Сборка
```bash
cmake -B build
cmake --build build
./build/cmake_task
```

## Объяснение команд CMakeLists.txt

| Команда | Что делает |
|---|---|
| `cmake_minimum_required` | Минимальная версия CMake для сборки |
| `project` | Название проекта и язык |
| `add_subdirectory` | Подключает дочернюю папку с её CMakeLists.txt |
| `add_library` | Создаёт библиотеку (STATIC/SHARED) из указанных файлов |
| `add_executable` | Создаёт исполняемый файл |
| `target_include_directories` | Указывает папку с заголовками для цели |
| `target_link_libraries` | Линкует цель с библиотеками |
| `PRIVATE` | Зависимость только внутри цели, не передаётся дальше |
| `PUBLIC` | Зависимость внутри цели и передаётся всем, кто линкуется с целью |
