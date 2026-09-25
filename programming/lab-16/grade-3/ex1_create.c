/*
 * Упражнение 1 — Создать поток
 *
 * pthread_create() запускает функцию в новом потоке. Родительский поток
 * (main) и дочерний работают параллельно. Каждый печатает по 5 строк.
 * Без pthread_join родитель может закончиться раньше ребёнка.
 */
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *child(void *arg) {
    (void)arg;
    for (int i = 0; i < 5; i++) {
        printf("child:  line %d\n", i + 1);
        usleep(50 * 1000);  /* небольшая пауза, чтобы потоки перемешались */
    }
    return NULL;
}

int main(void) {
    pthread_t tid;
    if (pthread_create(&tid, NULL, child, NULL) != 0) {
        perror("pthread_create");
        return 1;
    }

    for (int i = 0; i < 5; i++) {
        printf("parent: line %d\n", i + 1);
        usleep(50 * 1000);
    }

    /* Без join родитель завершится и потащит за собой ребёнка.
     * Для демонстрации параллельности оставляем join только в ex2. */
    pthread_join(tid, NULL);
    return 0;
}
