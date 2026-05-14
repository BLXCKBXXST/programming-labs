#include <stdio.h>

typedef struct {
    int a;
    int b;
} Fraction;

Fraction make_fraction(int a, int b);
Fraction mul_fraction(Fraction x, Fraction y);
Fraction div_fraction(Fraction x, Fraction y);

void print_fraction(Fraction f);