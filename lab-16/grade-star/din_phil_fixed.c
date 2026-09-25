/*
 * Обедающие философы — БЕЗ дедлока.
 *
 * Стратегия: асимметричный захват вилок.
 *   - философы с чётным id берут сначала ЛЕВУЮ вилку, затем правую;
 *   - философы с нечётным id берут сначала ПРАВУЮ, затем левую.
 *
 * Это убирает циклическую зависимость в графе ожидания, что и было
 * причиной дедлока в исходной версии (все берут правую → все ждут левую).
 *
 * Альтернатива — мьютекс "officier" (разрешает одновременно есть только
 * PHILO-1 философам). Здесь использовать асимметричный захват, он проще.
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
pthread_t       phils[PHILO];
pthread_mutex_t foodlock;

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
    int left_fork  = (id + 1) % PHILO;
    int right_fork = id;
    int f;

    printf("Philosopher %d sitting down to dinner.\n", id);

    while ((f = food_on_table())) {
        printf("Philosopher %d: get dish %d.\n", id, f);

        /* асимметричный захват — ключ к отсутствию дедлока */
        if (id % 2 == 0) {
            get_fork(id, left_fork,  "left ");
            get_fork(id, right_fork, "right");
        } else {
            get_fork(id, right_fork, "right");
            get_fork(id, left_fork,  "left ");
        }

        printf("Philosopher %d: eating.\n", id);
        usleep(DELAY * (FOOD - f + 1));
        down_forks(left_fork, right_fork);
    }
    printf("Philosopher %d is done eating.\n", id);
    return NULL;
}

int main(void) {
    pthread_mutex_init(&foodlock, NULL);
    for (int i = 0; i < PHILO; i++) pthread_mutex_init(&forks[i], NULL);
    for (int i = 0; i < PHILO; i++) pthread_create(&phils[i], NULL, philosopher, (void *)(long)i);
    for (int i = 0; i < PHILO; i++) pthread_join(phils[i], NULL);
    return 0;
}
