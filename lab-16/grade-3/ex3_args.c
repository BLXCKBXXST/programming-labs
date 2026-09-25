/*
 * Упражнение 3 — Параметры потока
 *
 * Создаются 4 потока, исполняющих одну функцию `worker()`.
 * Каждому передаётся свой список строк (структура SetOfLines).
 * Потоки печатают свои строки параллельно — выводы перемешиваются.
 */
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

typedef struct {
    const char *name;
    const char *lines[5];
} SetOfLines;

void *worker(void *arg) {
    SetOfLines *set = (SetOfLines *)arg;
    for (int i = 0; i < 5; i++) {
        printf("[%s] %s\n", set->name, set->lines[i]);
        usleep(30 * 1000);
    }
    return NULL;
}

int main(void) {
    SetOfLines sets[4] = {
        {"A", {"apple",  "ant",    "axe",    "arrow",  "atom"}},
        {"B", {"bread",  "ball",   "bat",    "bicycle","book"}},
        {"C", {"cat",    "cake",   "cup",    "comet",  "cloud"}},
        {"D", {"dog",    "drum",   "dice",   "desk",   "deer"}},
    };

    pthread_t tids[4];
    for (int i = 0; i < 4; i++) {
        pthread_create(&tids[i], NULL, worker, &sets[i]);
    }
    for (int i = 0; i < 4; i++) {
        pthread_join(tids[i], NULL);
    }
    return 0;
}
