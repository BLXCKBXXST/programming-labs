/*
 * Упражнение 9 — Замер времени перемножения матриц
 *
 * То же, что ex8_matmul, но без печати и с замером общего времени
 * (от старта первого pthread_create до конца последнего pthread_join).
 *
 * Вывод одна строка: "N,threads,time_ms".
 * Запускается из benchmark.py для серии N × threads.
 */
#define _POSIX_C_SOURCE 199309L     /* для clock_gettime / CLOCK_MONOTONIC */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

static double now_sec(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s N threads\n", argv[0]);
        return 1;
    }
    int N = atoi(argv[1]);
    int T = atoi(argv[2]);
    if (N < 1 || T < 1) return 1;
    if (T > N) T = N;

    int *A = malloc((size_t)N * N * sizeof(int));
    int *B = malloc((size_t)N * N * sizeof(int));
    int *C = calloc((size_t)N * N, sizeof(int));
    for (int i = 0; i < N * N; i++) { A[i] = 1; B[i] = 1; }

    pthread_t *tids = malloc((size_t)T * sizeof(pthread_t));
    TaskArg   *args = malloc((size_t)T * sizeof(TaskArg));

    int chunk = N / T;

    double start = now_sec();
    for (int t = 0; t < T; t++) {
        args[t].start_row = t * chunk;
        args[t].end_row   = (t == T - 1) ? N : (t + 1) * chunk;
        args[t].N = N;
        args[t].A = A; args[t].B = B; args[t].C = C;
        pthread_create(&tids[t], NULL, worker, &args[t]);
    }
    for (int t = 0; t < T; t++) pthread_join(tids[t], NULL);
    double elapsed_ms = (now_sec() - start) * 1000.0;

    printf("%d,%d,%.3f\n", N, T, elapsed_ms);

    free(tids); free(args);
    free(A); free(B); free(C);
    return 0;
}
