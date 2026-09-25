/*
 * Упражнение 2 — Ожидание потока (pthread_join)
 *
 * Родительский поток сначала ждёт завершения дочернего,
 * только потом печатает свои строки.
 */
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *child(void *arg) {
    (void)arg;
    for (int i = 0; i < 5; i++) {
        printf("child:  line %d\n", i + 1);
        usleep(50 * 1000);
    }
    return NULL;
}

int main(void) {
    pthread_t tid;
    pthread_create(&tid, NULL, child, NULL);

    pthread_join(tid, NULL);   /* ждём, пока ребёнок не закончит */

    for (int i = 0; i < 5; i++) {
        printf("parent: line %d\n", i + 1);
    }
    return 0;
}
