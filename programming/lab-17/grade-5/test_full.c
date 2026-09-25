/*
 * Оценка 5 — расширенный набор unit-тестов на CMocka.
 * Каждый тест регистрируется как отдельная ctest-цель, чтобы получить
 * красивый цветной вывод "X/Y Test #N: name ... Passed".
 */
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <math.h>
#include "tinyexpr.h"

#define EPS 1e-9

/* ----- 1. Базовая арифметика ----- */

static void test_addition(void **state)       { (void)state; int e=0; assert_true(fabs(te_interp("1+2",&e)-3) < EPS); assert_int_equal(e, 0); }
static void test_subtraction(void **state)    { (void)state; int e=0; assert_true(fabs(te_interp("10-4",&e)-6) < EPS); assert_int_equal(e, 0); }
static void test_multiplication(void **state) { (void)state; int e=0; assert_true(fabs(te_interp("6*7",&e)-42) < EPS); assert_int_equal(e, 0); }
static void test_division(void **state)       { (void)state; int e=0; assert_true(fabs(te_interp("100/4",&e)-25) < EPS); assert_int_equal(e, 0); }

/* ----- 2. Приоритет и скобки ----- */

static void test_precedence(void **state) {
    (void)state; int e=0;
    assert_true(fabs(te_interp("2 + 3 * 4", &e) - 14.0) < EPS);
    assert_int_equal(e, 0);
}

static void test_parentheses(void **state) {
    (void)state; int e=0;
    assert_true(fabs(te_interp("(2 + 3) * 4", &e) - 20.0) < EPS);
    assert_int_equal(e, 0);
}

static void test_unary_minus(void **state) {
    (void)state; int e=0;
    assert_true(fabs(te_interp("-5 + 3", &e) - (-2.0)) < EPS);
    assert_int_equal(e, 0);
}

/* ----- 3. Степень ----- */

static void test_power_small(void **state) {
    (void)state; int e=0;
    assert_true(fabs(te_interp("2^10", &e) - 1024.0) < EPS);
    assert_int_equal(e, 0);
}

static void test_power_left_assoc(void **state) {
    (void)state; int e=0;
    /* tinyexpr ассоциирует ^ слева: 2^3^2 = (2^3)^2 = 8^2 = 64.
     * Это нестандартно для математики (обычно ^ право-ассоциативна),
     * и тест фиксирует фактическое поведение библиотеки. */
    assert_true(fabs(te_interp("2^3^2", &e) - 64.0) < EPS);
    assert_int_equal(e, 0);
}

/* ----- 4. Встроенные функции ----- */

static void test_sqrt(void **state) {
    (void)state; int e=0;
    assert_true(fabs(te_interp("sqrt(144)", &e) - 12.0) < EPS);
    assert_int_equal(e, 0);
}

static void test_abs(void **state) {
    (void)state; int e=0;
    assert_true(fabs(te_interp("abs(-7)", &e) - 7.0) < EPS);
    assert_int_equal(e, 0);
}

static void test_pow_function(void **state) {
    (void)state; int e=0;
    assert_true(fabs(te_interp("pow(2, 8)", &e) - 256.0) < EPS);
    assert_int_equal(e, 0);
}

static void test_log_ln(void **state) {
    (void)state; int e=0;
    /* ln(e) = 1 */
    assert_true(fabs(te_interp("ln(e)", &e) - 1.0) < EPS);
    assert_int_equal(e, 0);
}

static void test_pi_constant(void **state) {
    (void)state; int e=0;
    /* pi ≈ 3.14159265 */
    double pi = te_interp("pi", &e);
    assert_int_equal(e, 0);
    assert_true(fabs(pi - 3.14159265358979) < 1e-6);
}

/* ----- 5. Тригонометрия ----- */

static void test_sin_zero(void **state)   { (void)state; int e=0; assert_true(fabs(te_interp("sin(0)", &e)) < EPS); assert_int_equal(e, 0); }
static void test_cos_zero(void **state)   { (void)state; int e=0; assert_true(fabs(te_interp("cos(0)", &e) - 1.0) < EPS); assert_int_equal(e, 0); }

static void test_pythagorean(void **state) {
    (void)state; int e=0;
    /* sin²(0.7) + cos²(0.7) = 1 */
    double r = te_interp("sin(0.7)^2 + cos(0.7)^2", &e);
    assert_int_equal(e, 0);
    assert_true(fabs(r - 1.0) < EPS);
}

/* ----- 6. Особые значения ----- */

static void test_division_by_zero(void **state) {
    (void)state; int e=0;
    double r = te_interp("1/0", &e);
    assert_int_equal(e, 0);
    assert_true(isinf(r));
}

static void test_sqrt_of_negative(void **state) {
    (void)state; int e=0;
    double r = te_interp("sqrt(-1)", &e);
    assert_int_equal(e, 0);
    assert_true(isnan(r));
}

/* ----- 7. Синтаксические ошибки ----- */

static void test_error_trailing_op(void **state) {
    (void)state; int e=0;
    te_interp("1 +", &e);
    assert_true(e > 0);
}

static void test_error_unclosed_paren(void **state) {
    (void)state; int e=0;
    te_interp("(1 + 2", &e);
    assert_true(e > 0);
}

static void test_error_unknown_func(void **state) {
    (void)state; int e=0;
    te_interp("foo(1)", &e);
    assert_true(e > 0);
}

static void test_error_empty_string(void **state) {
    (void)state; int e=0;
    te_interp("", &e);
    assert_true(e > 0);
}

/* ----- main ----- */

int main(void) {
    const struct CMUnitTest tests[] = {
        /* арифметика */
        cmocka_unit_test(test_addition),
        cmocka_unit_test(test_subtraction),
        cmocka_unit_test(test_multiplication),
        cmocka_unit_test(test_division),
        /* приоритет */
        cmocka_unit_test(test_precedence),
        cmocka_unit_test(test_parentheses),
        cmocka_unit_test(test_unary_minus),
        /* степень */
        cmocka_unit_test(test_power_small),
        cmocka_unit_test(test_power_left_assoc),
        /* функции */
        cmocka_unit_test(test_sqrt),
        cmocka_unit_test(test_abs),
        cmocka_unit_test(test_pow_function),
        cmocka_unit_test(test_log_ln),
        cmocka_unit_test(test_pi_constant),
        /* тригонометрия */
        cmocka_unit_test(test_sin_zero),
        cmocka_unit_test(test_cos_zero),
        cmocka_unit_test(test_pythagorean),
        /* особые значения */
        cmocka_unit_test(test_division_by_zero),
        cmocka_unit_test(test_sqrt_of_negative),
        /* ошибки */
        cmocka_unit_test(test_error_trailing_op),
        cmocka_unit_test(test_error_unclosed_paren),
        cmocka_unit_test(test_error_unknown_func),
        cmocka_unit_test(test_error_empty_string),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
