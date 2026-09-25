/*
 * Звёздочка. Спираль (улитка) N×N: числа 1..N*N идут по периметру,
 * сворачивая внутрь.
 *
 * Пример N=4:
 *    1  2  3  4
 *   12 13 14  5
 *   11 16 15  6
 *   10  9  8  7
 */
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    printf("N: ");
    if (scanf("%d", &n) != 1 || n < 1 || n > 20) {
        printf("invalid N (1..20)\n");
        return 1;
    }

    int *a = calloc((size_t)n * n, sizeof(int));
    if (!a) {
        printf("oom\n");
        return 1;
    }

    int top = 0, bottom = n - 1, left = 0, right = n - 1;
    int v = 1;
    while (top <= bottom && left <= right) {
        for (int j = left; j <= right; j++)    a[top * n + j]    = v++;
        top++;
        for (int i = top; i <= bottom; i++)    a[i * n + right]  = v++;
        right--;
        if (top <= bottom) {
            for (int j = right; j >= left; j--) a[bottom * n + j] = v++;
            bottom--;
        }
        if (left <= right) {
            for (int i = bottom; i >= top; i--) a[i * n + left]   = v++;
            left++;
        }
    }

    int width = 1;
    for (int t = n * n; t >= 10; t /= 10) width++;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%*d%c", width, a[i * n + j], j + 1 == n ? '\n' : ' ');
        }
    }

    free(a);
    return 0;
}
