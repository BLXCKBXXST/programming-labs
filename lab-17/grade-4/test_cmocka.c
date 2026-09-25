/*
 * Оценка 4 — unit-тесты на фреймворке CMocka.
 * Используем табличные тесты, чтобы не плодить функции на каждый кейс.
 */
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <math.h>
#include "tinyexpr.h"

/* ---------- табличные тесты на корректные выражения ---------- */

struct ok_case {
    const char *expr;
    double      expected;
};

static const struct ok_case ok_cases[] = {
    /* арифметика */
    {"1+2",          3.0},
    {"100 - 25",     75.0},
    {"7 * 8",        56.0},
    {"81 / 9",       9.0},

    /* приоритет операций */
    {"2 + 3 * 4",    14.0},
    {"(2 + 3) * 4",  20.0},
    {"-3 + 5",       2.0},

    /* степень — правая ассоциативность */
    {"2^3",          8.0},
    {"2^10",         1024.0},

    /* встроенные функции */
    {"sqrt(144)",    12.0},
    {"abs(-7)",      7.0},
    {"pow(2, 8)",    256.0},
};

static void test_ok_cases(void **state) {
    (void)state;
    for (size_t i = 0; i < sizeof ok_cases / sizeof ok_cases[0]; i++) {
        int err = 0;
        double got = te_interp(ok_cases[i].expr, &err);
        assert_int_equal(err, 0);
        assert_true(fabs(got - ok_cases[i].expected) < 1e-9);
    }
}

/* ---------- табличные тесты на синтаксические ошибки ---------- */

struct err_case {
    const char *expr;
    int         min_error_pos;   /* позиция должна быть >= этой */
};

static const struct err_case err_cases[] = {
    {"1 +",       1},
    {"(1+2",      1},
    {"foo bar",   1},
    {"*5",        1},
    {"sqrt(",     1},
};

static void test_error_cases(void **state) {
    (void)state;
    for (size_t i = 0; i < sizeof err_cases / sizeof err_cases[0]; i++) {
        int err = 0;
        te_interp(err_cases[i].expr, &err);
        assert_true(err >= err_cases[i].min_error_pos);
    }
}

/* ---------- особые значения ---------- */

static void test_division_by_zero(void **state) {
    (void)state;
    int err = 0;
    double got = te_interp("1/0", &err);
    assert_int_equal(err, 0);            /* парсинг успешен */
    assert_true(isinf(got));             /* результат — бесконечность */
}

static void test_sqrt_of_negative(void **state) {
    (void)state;
    int err = 0;
    double got = te_interp("sqrt(-1)", &err);
    assert_int_equal(err, 0);
    assert_true(isnan(got));
}

static void test_trig_identity(void **state) {
    (void)state;
    int err = 0;
    /* sin²(0.5) + cos²(0.5) ≈ 1 */
    double got = te_interp("sin(0.5)^2 + cos(0.5)^2", &err);
    assert_int_equal(err, 0);
    assert_true(fabs(got - 1.0) < 1e-9);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_ok_cases),
        cmocka_unit_test(test_error_cases),
        cmocka_unit_test(test_division_by_zero),
        cmocka_unit_test(test_sqrt_of_negative),
        cmocka_unit_test(test_trig_identity),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
