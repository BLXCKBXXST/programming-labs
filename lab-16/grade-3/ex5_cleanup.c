/*
 * Упражнение 5 — Обработка завершения через pthread_cleanup_push
 *
 * Если поток отменили в середине работы, обычные return /exit не сработают.
 * pthread_cleanup_push() регистрирует функцию-уборщик, которая вызовется
 * при отмене (или при pthread_cleanup_pop(1)).
 *
 * Здесь cleanup-функция печатает прощальное сообщение, чтобы было видно,
 * что отменённые потоки успели прибраться за собой.
 */
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void cleanup(void *arg) {
    int id = *(int *)arg;
    printf("worker %d: cleanup — saying goodbye\n", id);
}

void *worker(void *arg) {
    int id = *(int *)arg;

    pthread_cleanup_push(cleanup, arg);

    for (int i = 0; ; i++) {
        printf("worker %d: tick %d\n", id, i);
        sleep(1);
    }

    /* pop(0) — не выполнять cleanup; pop(1) — выполнить.
     * Здесь до pop мы не дойдём, потому что нас отменят. */
    pthread_cleanup_pop(0);
    return NULL;
}

int main(void) {
    enum { N = 3 };
    pthread_t tids[N];
    int ids[N];

    for (int i = 0; i < N; i++) {
        ids[i] = i + 1;
        pthread_create(&tids[i], NULL, worker, &ids[i]);
    }

    sleep(2);
    printf("main: cancelling workers\n");

    for (int i = 0; i < N; i++) {
        pthread_cancel(tids[i]);
        pthread_join(tids[i], NULL);
    }
    printf("main: done\n");
    return 0;
}
