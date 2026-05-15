/*
 * Простая блокирующая FIFO-очередь сообщений (PDF упр 10).
 *
 * — msgSend: кладёт строку, обрезает до 128 символов, блокируется,
 *   пока очередь содержит больше 10 записей.
 * — msgRecv: извлекает первую запись, обрезает до bufsize,
 *   блокируется при пустой очереди.
 *
 * Под звёздочкой добавлен msgDrop() — будит всех ожидающих и
 * заставляет их вернуть -1.
 */
#ifndef MSGQUEUE_H
#define MSGQUEUE_H

#include <pthread.h>
#include <stddef.h>

#define MSG_MAX_LEN  128
#define Q_CAPACITY    10

typedef struct {
    char            data[Q_CAPACITY][MSG_MAX_LEN + 1];  /* +1 на '\0' */
    int             head;       /* индекс на чтение */
    int             tail;       /* индекс на запись */
    int             count;      /* сколько записей сейчас в очереди */
    int             dropped;    /* флаг "очередь закрыта", выставляется msgDrop */
    pthread_mutex_t lock;
    pthread_cond_t  not_full;   /* «есть свободный слот для отправителя» */
    pthread_cond_t  not_empty;  /* «есть данные для получателя» */
} Queue;

void  q_init(Queue *q);
void  q_destroy(Queue *q);

/* Возвращает число записанных символов или -1 при q_drop. */
int   msgSend(Queue *q, const char *msg);

/* Возвращает число прочитанных символов или -1 при q_drop. */
int   msgRecv(Queue *q, char *buf, size_t bufsize);

/* «Закрывает» очередь и будит всех ожидающих. После msgDrop send/recv возвращают -1. */
void  msgDrop(Queue *q);

#endif
