# Лабораторная №17 — Модульное тестирование

Тестирование сторонней библиотеки [tinyexpr](external/tinyexpr) для вычисления арифметических выражений. Библиотека хранится без изменений, её лицензия — [LICENSE](external/tinyexpr/LICENSE).

| Оценка | Тесты | Файл |
|---|---|---|
| 3 | `assert.h`, 12 проверок | [grade-3/test_simple.c](grade-3/test_simple.c) |
| 4 | CMocka, табличные проверки | [grade-4/test_cmocka.c](grade-4/test_cmocka.c) |
| 5 | CMocka, расширенный набор и запуск через CTest | [grade-5/test_full.c](grade-5/test_full.c) |

## Сборка и запуск

Нужны CMake и CMocka:

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

Либо `make test` из этой папки. Примеры тестовых случаев и подробности — в README соответствующих вариантов.
