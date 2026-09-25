#define _POSIX_C_SOURCE 200809L   /* нужно для strnlen */
#include "msgqueue.h"

#include <string.h>

void q_init(Queue *q) {
    q->head = 0;
    q->tail = 0;
    q->count = 0;
    q->dropped = 0;
    pthread_mutex_init(&q->lock, NULL);
    pthread_cond_init(&q->not_full, NULL);
    pthread_cond_init(&q->not_empty, NULL);
}

void q_destroy(Queue *q) {
    pthread_mutex_destroy(&q->lock);
    pthread_cond_destroy(&q->not_full);
    pthread_cond_destroy(&q->not_empty);
}

int msgSend(Queue *q, const char *msg) {
    /* обрезаем входное сообщение до MSG_MAX_LEN */
    size_t len = strnlen(msg, MSG_MAX_LEN);

    pthread_mutex_lock(&q->lock);
    while (q->count >= Q_CAPACITY && !q->dropped) {
        pthread_cond_wait(&q->not_full, &q->lock);
    }
    if (q->dropped) {
        pthread_mutex_unlock(&q->lock);
        return -1;
    }

    memcpy(q->data[q->tail], msg, len);
    q->data[q->tail][len] = '\0';
    q->tail = (q->tail + 1) % Q_CAPACITY;
    q->count++;

    pthread_cond_signal(&q->not_empty);
    pthread_mutex_unlock(&q->lock);
    return (int)len;
}

int msgRecv(Queue *q, char *buf, size_t bufsize) {
    if (bufsize == 0) return 0;

    pthread_mutex_lock(&q->lock);
    while (q->count == 0 && !q->dropped) {
        pthread_cond_wait(&q->not_empty, &q->lock);
    }
    if (q->dropped && q->count == 0) {
        pthread_mutex_unlock(&q->lock);
        return -1;
    }

    size_t copied = strnlen(q->data[q->head], MSG_MAX_LEN);
    if (copied > bufsize - 1) copied = bufsize - 1;
    memcpy(buf, q->data[q->head], copied);
    buf[copied] = '\0';

    q->head = (q->head + 1) % Q_CAPACITY;
    q->count--;

    pthread_cond_signal(&q->not_full);
    pthread_mutex_unlock(&q->lock);
    return (int)copied;
}

void msgDrop(Queue *q) {
    pthread_mutex_lock(&q->lock);
    q->dropped = 1;
    pthread_cond_broadcast(&q->not_full);
    pthread_cond_broadcast(&q->not_empty);
    pthread_mutex_unlock(&q->lock);
}
