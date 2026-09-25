#include "fraction.h"

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

void print_fraction(Fraction f) {
    printf("%d/%d", f.a, f.b);
}
