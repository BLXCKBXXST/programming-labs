/*
 * Упражнение 4 — Отмена потоков (pthread_cancel)
 *
 * Дочерние потоки печатают строку и засыпают на 1 секунду в цикле.
 * Через 2 секунды основной поток отменяет их через pthread_cancel().
 */
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *worker(void *arg) {
    int id = *(int *)arg;
    for (int i = 0; ; i++) {
        printf("worker %d: tick %d\n", id, i);
        sleep(1);   /* sleep — точка отмены (cancellation point) */
    }
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
    printf("main: 2 seconds passed, cancelling all workers\n");

    for (int i = 0; i < N; i++) {
        pthread_cancel(tids[i]);
        pthread_join(tids[i], NULL);
    }
    printf("main: done\n");
    return 0;
}
