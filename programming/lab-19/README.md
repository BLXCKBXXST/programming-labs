# Лаба 19. Банкомат

Консольный проект на C++17: меню, операции со счётом, журнал и восстановление данных после сбоя. Сборка через CMake, запуск из этой папки одной командой:

```bash
bash run.sh
```

Для тестов: `cmake -S . -B build && cmake --build build && ctest --test-dir build --output-on-failure`. Нужны CMake 3.20+ и Linux/macOS.
