# Оценка 4 — Unit-тесты на CMocka

## Что добавилось по сравнению с grade-3

- Используется **фреймворк** CMocka вместо голого `assert()`.
- Тесты группируются в **тест-сьюты**, при провале одного остальные всё равно выполняются.
- **Табличные тесты** — массив структур `{expr, expected}` + цикл, легко добавлять новые кейсы.
- Аккуратный вывод: `[ RUN ] ... [ OK ]`.

## Установка зависимости

```bash
sudo apt install libcmocka-dev   # Debian/Ubuntu
```

## Что тестируется

5 групп:

| Тест | Что проверяет |
|---|---|
| `test_ok_cases`         | 12 выражений с известным результатом (`1+2`, `2^10`, `sqrt(144)`, ...) |
| `test_error_cases`      | 5 невалидных строк — `err > 0` |
| `test_division_by_zero` | `1/0` → `inf` (не ошибка парсера) |
| `test_sqrt_of_negative` | `sqrt(-1)` → `NaN` |
| `test_trig_identity`    | `sin²(0.5) + cos²(0.5)` ≈ 1 |

## Запуск

```bash
make run
```

Ожидаемый вывод:

```
[==========] Running 5 test(s).
[ RUN      ] test_ok_cases
[       OK ] test_ok_cases
[ RUN      ] test_error_cases
[       OK ] test_error_cases
...
[  PASSED  ] 5 test(s).
```

## Ключевые макросы CMocka

| Макрос | Что делает |
|---|---|
| `cmocka_unit_test(fn)` | объявить тест-функцию |
| `cmocka_run_group_tests(arr, NULL, NULL)` | запустить, второй/третий аргумент — setup/teardown |
| `assert_int_equal(a, b)` | целочисленное равенство |
| `assert_true(cond)` | проверка условия |
| `assert_float_equal(a, b, eps)` | сравнение float с допуском (есть с CMocka ≥ 1.1) |
| `assert_string_equal(a, b)` | сравнение строк |

Подробнее: `man cmocka` или [официальная документация](https://api.cmocka.org).
