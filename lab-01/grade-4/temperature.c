#include <stdio.h>

int main(void) {
    double t;
    char unit;

    printf("Input temperature: ");
    if (scanf("%lf%c", &t, &unit) != 2) {
        printf("Ouput error\n");
        return 1;
    }

    if (unit == 'c' || unit == 'C') {
        double f = t * 9.0 / 5.0 + 32.0;
        printf("Ouput temperature: %.1ff\n", f);
    } else if (unit == 'f' || unit == 'F') {
        double c = (t - 32.0) * 5.0 / 9.0;
        printf("Ouput temperature: %.1fc\n", c);
    } else {
        printf("Ouput error\n");
        return 1;
    }

    return 0;
}
