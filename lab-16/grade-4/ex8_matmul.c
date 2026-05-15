/*
 * Упражнение 8 — Перемножение квадратных матриц NxN
 *
 * Использование: ./ex8_matmul N threads
 *   N       — размер матрицы (≥ 1)
 *   threads — количество рабочих потоков (≥ 1)
 *
 * Матрицы A и B заполняются единицами. Каждый поток считает свою
 * полосу строк матрицы C. Если N не кратен threads, остаток отдаётся
 * последнему потоку.
 *
 * При N < 5 печатаются все три матрицы (для самопроверки).
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int        start_row;
    int        end_row;
    int        N;
    const int *A;
    const int *B;
    int       *C;
} TaskArg;

static void *worker(void *arg) {
    TaskArg *t = (TaskArg *)arg;
    int N = t->N;
    for (int i = t->start_row; i < t->end_row; i++) {
        for (int j = 0; j < N; j++) {
            int sum = 0;
            for (int k = 0; k < N; k++) {
                sum += t->A[i * N + k] * t->B[k * N + j];
            }
            t->C[i * N + j] = sum;
        }
    }
    return NULL;
}

static void print_matrix(const char *name, const int *M, int N) {
    printf("%s =\n", name);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%4d ", M[i * N + j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s N threads\n", argv[0]);
        return 1;
    }
    int N = atoi(argv[1]);
    int T = atoi(argv[2]);
    if (N < 1 || T < 1) {
        fprintf(stderr, "N and threads must be >= 1\n");
        return 1;
    }
    if (T > N) T = N;  /* не больше потоков, чем строк */

    int *A = malloc((size_t)N * N * sizeof(int));
    int *B = malloc((size_t)N * N * sizeof(int));
    int *C = calloc((size_t)N * N, sizeof(int));
    if (!A || !B || !C) {
        fprintf(stderr, "oom\n");
        return 1;
    }
    for (int i = 0; i < N * N; i++) { A[i] = 1; B[i] = 1; }

    pthread_t *tids = malloc((size_t)T * sizeof(pthread_t));
    TaskArg   *args = malloc((size_t)T * sizeof(TaskArg));

    int chunk = N / T;
    for (int t = 0; t < T; t++) {
        args[t].start_row = t * chunk;
        args[t].end_row   = (t == T - 1) ? N : (t + 1) * chunk;
        args[t].N         = N;
        args[t].A = A; args[t].B = B; args[t].C = C;
        pthread_create(&tids[t], NULL, worker, &args[t]);
    }
    for (int t = 0; t < T; t++) pthread_join(tids[t], NULL);

    if (N < 5) {
        print_matrix("A", A, N);
        print_matrix("B", B, N);
        print_matrix("C", C, N);
    } else {
        /* для больших — проверка корректности: все C[i][j] должны быть = N */
        int ok = 1;
        for (int i = 0; i < N * N; i++) {
            if (C[i] != N) { ok = 0; break; }
        }
        printf("N=%d threads=%d: %s\n", N, T, ok ? "OK" : "FAIL");
    }

    free(tids); free(args);
    free(A); free(B); free(C);
    return 0;
}
