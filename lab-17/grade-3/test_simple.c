/*
 * Оценка 3 — простые unit-тесты на assert() без фреймворка.
 * Проверяем основные сценарии работы te_interp() из tinyexpr.
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include "tinyexpr.h"

#define EPS 1e-9

static void check(const char *expr, double expected) {
    int err = 0;
    double got = te_interp(expr, &err);
    if (err != 0) {
        printf("FAIL: \"%s\" — parse error at position %d\n", expr, err);
        assert(0);
    }
    if (fabs(got - expected) > EPS) {
        printf("FAIL: \"%s\" = %f, expected %f\n", expr, got, expected);
        assert(0);
    }
    printf("OK:   \"%s\" = %g\n", expr, got);
}

static void check_error(const char *expr) {
    int err = 0;
    te_interp(expr, &err);
    if (err == 0) {
        printf("FAIL: \"%s\" was expected to fail, but parsed OK\n", expr);
        assert(0);
    }
    printf("OK:   \"%s\" — error at position %d (as expected)\n", expr, err);
}

int main(void) {
    /* арифметика */
    check("1+2", 3.0);
    check("10 - 4", 6.0);
    check("6*7", 42.0);
    check("100 / 4", 25.0);

    /* приоритет и скобки */
    check("2 + 3 * 4", 14.0);
    check("(2 + 3) * 4", 20.0);

    /* степень и встроенные функции */
    check("2^10", 1024.0);
    check("sqrt(16)", 4.0);
    check("sin(0)", 0.0);

    /* ошибки разбора */
    check_error("1 +");
    check_error("foo");
    check_error("(1 + 2");

    printf("\nAll %d tests passed.\n", 12);
    return 0;
}
