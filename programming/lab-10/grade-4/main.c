#include "fraction.h"

int main(void) {
    Fraction f1, f2;

    printf("Введите дробь 1 (a b): ");
    scanf("%d %d", &f1.a, &f1.b);

    printf("Введите дробь 2 (a b): ");
    scanf("%d %d", &f2.a, &f2.b);

    Fraction prod = mul_fraction(f1, f2);
    Fraction quot = div_fraction(f1, f2);

    printf("f1 = ");
    print_fraction(f1);
    printf("\n");

    printf("f2 = ");
    print_fraction(f2);
    printf("\n");

    printf("f1 * f2 = ");
    print_fraction(prod);
    printf("\n");

    printf("f1 / f2 = ");
    print_fraction(quot);
    printf("\n");

    return 0;
}
