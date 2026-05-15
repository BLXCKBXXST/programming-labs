#include <stdio.h>

/*
 * Фикс: внутренний цикл начинаем с j = i + 1, чтобы пройти
 * только верхний треугольник матрицы.
 *
 * В исходном коде каждая пара (i,j) и (j,i) свопалась ДВАЖДЫ
 * (один раз при i=0,j=1 и второй раз при i=1,j=0). Два свопа
 * подряд возвращают элементы на место — матрица остаётся прежней.
 */

enum { N = 3 };

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void transpose(int m[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            swap(&m[i][j], &m[j][i]);
        }
    }
}

int main(void) {
    int m[N][N] = {{1, 2, 3},
                   {4, 5, 6},
                   {7, 8, 9}};

    transpose(m);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
    return 0;
}
