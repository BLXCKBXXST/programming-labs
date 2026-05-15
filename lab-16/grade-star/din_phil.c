/*
 * Классическая задача с обедающими философами и дедлоком.
 * Источник: https://github.com/kruffka/C-Programming/blob/2025-2026/16_threads/src/din_phil.c
 *
 * Сам код: пять философов сидят за круглым столом. У каждого слева
 * и справа лежит вилка (общая с соседом). Едят спагетти двумя вилками.
 *
 * Все философы берут СНАЧАЛА правую, потом левую вилку. При sleep_seconds = 0
 * на старте каждый философ хватает свою правую вилку — и ждёт левую,
 * которую уже держит сосед. Классический дедлок.
 *
 * Запуск:
 *   ./din_phil          # дедлок с большой вероятностью
 *   ./din_phil 1        # философ #1 спит 1 с перед захватом — остальные успевают
 */

#define _DEFAULT_SOURCE     /* для usleep */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define PHILO 5
#define DELAY 30000
#define FOOD 50

pthread_mutex_t forks[PHILO];
pthread_t phils[PHILO];
pthread_mutex_t foodlock;

int sleep_seconds = 0;

static int food_on_table(void) {
    static int food = FOOD;
    int myfood;
    pthread_mutex_lock(&foodlock);
    if (food > 0) food--;
    myfood = food;
    pthread_mutex_unlock(&foodlock);
    return myfood;
}

static void get_fork(int phil, int fork, const char *hand) {
    pthread_mutex_lock(&forks[fork]);
    printf("Philosopher %d: got %s fork %d\n", phil, hand, fork);
}

static void down_forks(int f1, int f2) {
    pthread_mutex_unlock(&forks[f1]);
    pthread_mutex_unlock(&forks[f2]);
}

static void *philosopher(void *num) {
    int id = (int)(long)num;
    int left_fork  = id + 1;
    int right_fork = id;
    int f;

    if (left_fork == PHILO) left_fork = 0;

    printf("Philosopher %d sitting down to dinner.\n", id);

    while ((f = food_on_table())) {
        if (id == 1) sleep(sleep_seconds);   /* костыль для деблокировки */

        printf("Philosopher %d: get dish %d.\n", id, f);
        get_fork(id, right_fork, "right");
        get_fork(id, left_fork,  "left ");

        printf("Philosopher %d: eating.\n", id);
        usleep(DELAY * (FOOD - f + 1));
        down_forks(left_fork, right_fork);
    }
    printf("Philosopher %d is done eating.\n", id);
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc == 2) sleep_seconds = atoi(argv[1]);

    pthread_mutex_init(&foodlock, NULL);
    for (int i = 0; i < PHILO; i++) pthread_mutex_init(&forks[i], NULL);
    for (int i = 0; i < PHILO; i++) pthread_create(&phils[i], NULL, philosopher, (void *)(long)i);
    for (int i = 0; i < PHILO; i++) pthread_join(phils[i], NULL);
    return 0;
}
