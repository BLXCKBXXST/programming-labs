# Лаба 17. Тестирование

Пробуем тестировать чужую библиотеку [tinyexpr](external/tinyexpr/) для арифметических выражений. Оригинальный код библиотеки не меняем; [лицензия](external/tinyexpr/LICENSE) лежит рядом.

[Простые assert](grade-3/), [CMocka](grade-4/) и [расширенный набор тестов с CTest](grade-5/). Для последних двух нужна установленная CMocka.

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

Можно короче: `make test`.
