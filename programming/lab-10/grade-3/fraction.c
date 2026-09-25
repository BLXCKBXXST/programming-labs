/*
 * Оценка 3 — Дроби (вариант 16 из PDF).
 *
 * Структура Fraction (числитель + знаменатель), четыре функции
 * (≥ 2 по требованию PDF), всё в одном файле.
 */
#include <stdio.h>

typedef struct {
    int a;   /* числитель */
    int b;   /* знаменатель */
} Fraction;

/* функция, принимающая структуру */
void print_fraction(Fraction f) {
    printf("%d/%d", f.a, f.b);
}

/* функция, возвращающая структуру */
Fraction make_fraction(int a, int b) {
    Fraction f;
    f.a = a;
    f.b = b;
    return f;
}

Fraction mul_fraction(Fraction x, Fraction y) {
    Fraction r;
    r.a = x.a * y.a;
    r.b = x.b * y.b;
    return r;
}

Fraction div_fraction(Fraction x, Fraction y) {
    Fraction r;
    r.a = x.a * y.b;
    r.b = x.b * y.a;
    return r;
}

int main(void) {
    Fraction f1, f2;

    printf("Введите дробь 1 (a b): ");
    scanf("%d %d", &f1.a, &f1.b);
    printf("Введите дробь 2 (a b): ");
    scanf("%d %d", &f2.a, &f2.b);

    Fraction prod = mul_fraction(f1, f2);
    Fraction quot = div_fraction(f1, f2);

    printf("f1 = ");      print_fraction(f1);   printf("\n");
    printf("f2 = ");      print_fraction(f2);   printf("\n");
    printf("f1 * f2 = "); print_fraction(prod); printf("\n");
    printf("f1 / f2 = "); print_fraction(quot); printf("\n");

    return 0;
}
