/*
 * Упражнение 7 — Синхронизированный вывод
 *
 * Родитель и ребёнок печатают строго по очереди: parent line 1,
 * child line 1, parent line 2, child line 2, ...
 *
 * Реализация: один mutex + один condition variable + общий счётчик
 * `turn`. Родитель ходит при чётном turn, ребёнок — при нечётном.
 */
#include <pthread.h>
#include <stdio.h>

#define LINES 5

static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t  cv   = PTHREAD_COND_INITIALIZER;
static int turn = 0;  /* 0 = ход родителя, 1 = ход ребёнка */

void *child(void *arg) {
    (void)arg;
    for (int i = 0; i < LINES; i++) {
        pthread_mutex_lock(&lock);
        while (turn != 1) {
            pthread_cond_wait(&cv, &lock);
        }
        printf("child:  line %d\n", i + 1);
        turn = 0;
        pthread_cond_signal(&cv);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main(void) {
    pthread_t tid;
    pthread_create(&tid, NULL, child, NULL);

    for (int i = 0; i < LINES; i++) {
        pthread_mutex_lock(&lock);
        while (turn != 0) {
            pthread_cond_wait(&cv, &lock);
        }
        printf("parent: line %d\n", i + 1);
        turn = 1;
        pthread_cond_signal(&cv);
        pthread_mutex_unlock(&lock);
    }

    pthread_join(tid, NULL);
    return 0;
}
