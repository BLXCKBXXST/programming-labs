#ifndef FRACTION_H
#define FRACTION_H

#include <stdio.h>

typedef struct {
    int a;   /* числитель */
    int b;   /* знаменатель */
} Fraction;

/* функции работают через указатели на структуру (как требует PDF на 5) */
void     read_fraction(Fraction *f);
void     print_fraction(const Fraction *f);
Fraction mul_fraction(const Fraction *x, const Fraction *y);
Fraction div_fraction(const Fraction *x, const Fraction *y);

#endif
