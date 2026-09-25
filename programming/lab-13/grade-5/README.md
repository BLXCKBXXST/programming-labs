# CMake с подпроектами

Задание из `cmake_task`: заполнить недостающие части CMakeLists в шаблонном проекте. Здесь несколько папок — `pipes/`, `background/` и основной `src/`. Подключаются через `add_subdirectory`, библиотеки — через `target_link_libraries`.

```bash
cmake -S . -B build
cmake --build build
./build/cmake_task
```

[Оригинальное задание](https://github.com/kruffka/C-Programming/tree/cmake_task).
