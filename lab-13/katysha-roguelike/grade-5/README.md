# Lab 13 — katysha-roguelike — Оценка 5

## Что реализовано

Включает всё из оценок 3 и 4, плюс:

### 9. Источник задания

Склонирована ветка `cmake_task` из:
> https://github.com/kruffka/C-Programming/tree/cmake_task

### 10. Структура проекта

```
grade-5/
├── CMakeLists.txt          — корневой
├── src/main.c
├── pipes/
│   ├── CMakeLists.txt        — статическая библиотека pipes
│   ├── pipes.h
│   ├── read_pipe.c
│   └── write_pipe.c
└── background/
    ├── CMakeLists.txt        — статическая библиотека background
    ├── background.h
    └── background.c
```

### 11. Команды в CMakeLists.txt

| Команда | Что делает |
|---|---|
| `cmake_minimum_required` | минимальная версия CMake |
| `project(...)` | имя проекта и язык |
| `add_subdirectory(pipes)` | подключает `pipes/CMakeLists.txt` |
| `add_subdirectory(background)` | подключает `background/CMakeLists.txt` |
| `add_library(pipes STATIC ...)` | создаёт статическую библиотеку из файлов |
| `target_include_directories(... PUBLIC ...)` | кто линкуется — видит заголовки |
| `target_link_libraries(... PRIVATE pipes)` | `background` зависит от `pipes`, но наружу это не пробрасывается |
| `add_executable(cmake_task ...)` | создаёт исполняемый файл |

**PUBLIC vs PRIVATE:**
- `PUBLIC` — доступно и внутри таргета, и всем кто на него линкуется
- `PRIVATE` — только внутри таргета, наружу не пробрасывается

## Сборка и запуск

```bash
cmake -B build
cmake --build build
./build/cmake_task
```
