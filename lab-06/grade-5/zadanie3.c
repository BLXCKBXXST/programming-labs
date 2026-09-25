#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Оценка 5: Метод Крамера для СЛАУ произвольного размера N

#define EPS 1e-9

double **alloc_matrix(int n) {
    double **a = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++)
        a[i] = (double *)malloc(n * sizeof(double));
    return a;
}

void free_matrix(double **a, int n) {
    for (int i = 0; i < n; i++) free(a[i]);
    free(a);
}

void copy_matrix(double **dst, double **src, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dst[i][j] = src[i][j];
}

void print_matrix(double **A, double *b, int n) {
    printf("\nМатрица системы (A | b):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%8.2f", A[i][j]);
        printf(" | %8.2f\n", b[i]);
    }
}

double det_gauss(double **A, int n) {
    double **M = alloc_matrix(n);
    copy_matrix(M, A, n);

    int swaps = 0;
    for (int col = 0; col < n; col++) {
        int pivot = col;
        for (int row = col + 1; row < n; row++)
            if (fabs(M[row][col]) > fabs(M[pivot][col]))
                pivot = row;

        if (fabs(M[pivot][col]) < EPS) { free_matrix(M, n); return 0.0; }

        if (pivot != col) {
            double *tmp = M[pivot]; M[pivot] = M[col]; M[col] = tmp;
            swaps++;
        }
        for (int row = col + 1; row < n; row++) {
            double f = M[row][col] / M[col][col];
            for (int k = col; k < n; k++)
                M[row][k] -= f * M[col][k];
        }
    }
    double det = (swaps % 2 == 0) ? 1.0 : -1.0;
    for (int i = 0; i < n; i++) det *= M[i][i];
    free_matrix(M, n);
    return det;
}

void replace_col(double **T, double **A, double *b, int n, int col) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            T[i][j] = (j == col) ? b[i] : A[i][j];
}

int main(void) {
    int n;
    printf("Введите размер системы N: ");
    if (scanf("%d", &n) != 1 || n <= 0) { printf("Некорректный N\n"); return 1; }

    double **A = alloc_matrix(n);
    double *b = (double *)malloc(n * sizeof(double));
    double *x = (double *)calloc(n, sizeof(double));

    printf("Введите матрицу коэффициентов (%dx%d) построчно:\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%lf", &A[i][j]);

    printf("Введите вектор правых частей (%d значения):\n", n);
    for (int i = 0; i < n; i++)
        scanf("%lf", &b[i]);

    print_matrix(A, b, n);

    double detA = det_gauss(A, n);
    if (fabs(detA) < EPS) {
        printf("\nНет единственного решения (det = 0)\n");
        free(x); free(b); free_matrix(A, n);
        return 0;
    }

    double **T = alloc_matrix(n);
    for (int k = 0; k < n; k++) {
        replace_col(T, A, b, n, k);
        x[k] = det_gauss(T, n) / detA;
    }
    free_matrix(T, n);

    printf("\nРешение (метод Крамера):\n");
    for (int i = 0; i < n; i++)
        printf("x[%d] = %.6f\n", i + 1, x[i]);

    free(x); free(b); free_matrix(A, n);
    return 0;
}
