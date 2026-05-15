/*
 * Односторонний чат через FIFO-очередь сообщений.
 *
 * 3 клиента-продюсера: каждый раз в 100–500 мс шлёт сообщение
 *                      "[Client N] iteration K".
 * 2 сервера-консьюмера: читают и печатают "[Client N] iteration K"
 *                       в формате PDF, потом спят случайно.
 *
 * Работаем 5 секунд, затем msgDrop, ждём завершения потоков.
 */
#define _DEFAULT_SOURCE       /* для usleep, sleep, clock_gettime */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "msgqueue.h"

#define DURATION_SEC  5
#define N_CLIENTS     3
#define N_SERVERS     2

static Queue g_queue;

/* очень простой PRNG со своим состоянием — чтобы не дёргать общий rand() */
static unsigned next_rand(unsigned *state) {
    *state = *state * 1103515245u + 12345u;
    return (*state / 65536u) % 32768u;
}

static int g_running = 1;

typedef struct {
    int        id;
    unsigned   seed;
} Role;

static void *client(void *arg) {
    Role *r = (Role *)arg;
    int iter = 0;
    while (g_running) {
        char msg[64];
        snprintf(msg, sizeof msg, "[Client %d] message %d", r->id, iter++);
        if (msgSend(&g_queue, msg) < 0) break;
        usleep((next_rand(&r->seed) % 400 + 100) * 1000);
    }
    return NULL;
}

static void *server(void *arg) {
    Role *r = (Role *)arg;
    char buf[160];
    while (g_running) {
        int n = msgRecv(&g_queue, buf, sizeof buf);
        if (n < 0) break;
        printf("server #%d got: %s\n", r->id, buf);
        usleep((next_rand(&r->seed) % 200 + 50) * 1000);
    }
    return NULL;
}

int main(void) {
    q_init(&g_queue);

    pthread_t clients[N_CLIENTS], servers[N_SERVERS];
    Role      c_roles[N_CLIENTS], s_roles[N_SERVERS];

    for (int i = 0; i < N_CLIENTS; i++) {
        c_roles[i].id   = i + 1;
        c_roles[i].seed = 1234u + i * 7919u;
        pthread_create(&clients[i], NULL, client, &c_roles[i]);
    }
    for (int i = 0; i < N_SERVERS; i++) {
        s_roles[i].id   = i + 1;
        s_roles[i].seed = 9001u + i * 4231u;
        pthread_create(&servers[i], NULL, server, &s_roles[i]);
    }

    sleep(DURATION_SEC);
    printf("--- main: stopping chat ---\n");
    g_running = 0;
    msgDrop(&g_queue);   /* будим всех заблокированных */

    for (int i = 0; i < N_CLIENTS; i++) pthread_join(clients[i], NULL);
    for (int i = 0; i < N_SERVERS; i++) pthread_join(servers[i], NULL);

    q_destroy(&g_queue);
    printf("--- main: done ---\n");
    return 0;
}
