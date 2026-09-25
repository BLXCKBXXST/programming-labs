#include <stdio.h>
#include <math.h>

int main(void) {
    double x, y;
    printf("x y: ");
    if (scanf("%lf %lf", &x, &y) != 2) {
        printf("Invalid input\n");
        return 1;
    }

    // Область ограничена квадратом [-1, 1] × [-1, 1] и прямыми y = ±x.
    // Включаются точки с y >= -|x|.
    int inside =
        (x >= -1.0 && x <= 1.0) &&
        (y >= -1.0 && y <= 1.0) &&
        (y >= -fabs(x));

    printf("%s\n", inside ? "YES" : "NO");
    return 0;
}
