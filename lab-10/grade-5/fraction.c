#include "fraction.h"

void read_fraction(Fraction *f) {
    scanf("%d %d", &f->a, &f->b);
}

void print_fraction(const Fraction *f) {
    printf("%d/%d", f->a, f->b);
}

Fraction mul_fraction(const Fraction *x, const Fraction *y) {
    Fraction r;
    r.a = x->a * y->a;
    r.b = x->b * y->b;
    return r;
}

Fraction div_fraction(const Fraction *x, const Fraction *y) {
    Fraction r;
    r.a = x->a * y->b;
    r.b = x->b * y->a;
    return r;
}
