#include <stdio.h>

// Оценка 4: Метод Крамера для СЛАУ NxN, N от 2 до 3

double det2(double m[3][3], int n) {
    if (n == 2)
        return m[0][0]*m[1][1] - m[0][1]*m[1][0];
    return m[0][0]*(m[1][1]*m[2][2] - m[1][2]*m[2][1])
          -m[0][1]*(m[1][0]*m[2][2] - m[1][2]*m[2][0])
          +m[0][2]*(m[1][0]*m[2][1] - m[1][1]*m[2][0]);
}

int main() {
    int N;
    printf("Введите N (2 или 3): ");
    scanf("%d", &N);
    if (N < 2 || N > 3) {
        printf("Ошибка: N должно быть 2 или 3\n");
        return 1;
    }

    double A[3][3], b[3];

    printf("Введите матрицу коэффициентов (%dx%d) построчно:\n", N, N);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            scanf("%lf", &A[i][j]);

    printf("Введите вектор правых частей (%d значения):\n", N);
    for (int i = 0; i < N; i++)
        scanf("%lf", &b[i]);

    printf("\nМатрица системы:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%8.2f", A[i][j]);
        printf(" | %8.2f\n", b[i]);
    }

    double detA = det2(A, N);
    if (detA == 0.0) {
        printf("\nНет единственного решения (det = 0)\n");
        return 0;
    }

    printf("\nРешение (метод Крамера):\n");
    double T[3][3];
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                T[i][j] = (j == k) ? b[i] : A[i][j];
        double xi = det2(T, N) / detA;
        printf("x[%d] = %.2f\n", k + 1, xi);
    }
    return 0;
}
