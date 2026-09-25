# Оценка 5 — Очередь сообщений + односторонний чат

Реализация по упражнению 10 из PDF: блокирующая FIFO-очередь и многопоточный чат с несколькими клиентами и серверами.

## Файлы

| Файл | Что делает |
|---|---|
| [msgqueue.h](msgqueue.h) | Объявление структуры `Queue` и функций `msgSend / msgRecv / msgDrop` |
| [msgqueue.c](msgqueue.c) | Кольцевой буфер на 10 слотов + `pthread_mutex_t` + 2 `pthread_cond_t` |
| [chat.c](chat.c)         | 3 клиента-продюсера + 2 сервера-консьюмера, 5 секунд работы |

## API очереди

```c
int  msgSend(Queue *q, const char *msg);
//   обрезает msg до 128 символов, кладёт в очередь.
//   блокируется, если в очереди > 10 записей.
//   возвращает число записанных символов, либо -1 после msgDrop.

int  msgRecv(Queue *q, char *buf, size_t bufsize);
//   извлекает первую запись, обрезает до bufsize, копирует в buf.
//   блокируется, если очередь пуста.
//   возвращает число прочитанных символов, либо -1 после msgDrop.

void msgDrop(Queue *q);
//   будит всех ожидающих, после чего send/recv возвращают -1.
```

## Сборка и запуск

```bash
make all
./chat
# работает 5 секунд, затем останавливается через msgDrop
```

Ожидаемый вывод (пример):

```
server #1 got: [Client 1] message 0
server #2 got: [Client 2] message 0
server #2 got: [Client 3] message 0
server #1 got: [Client 3] message 1
...
--- main: stopping chat ---
--- main: done ---
```

## Как работает синхронизация

Очередь — кольцевой буфер на 10 строк. Все операции защищены **одним** мьютексом `lock`. Когда очередь полна, `msgSend` ждёт на `not_full`; когда пуста, `msgRecv` ждёт на `not_empty`. Каждая успешная операция будит ровно одного ждущего через `pthread_cond_signal`.

```c
/* msgSend */
pthread_mutex_lock(&q->lock);
while (q->count >= Q_CAPACITY && !q->dropped)
    pthread_cond_wait(&q->not_full, &q->lock);
/* ... запись ... */
pthread_cond_signal(&q->not_empty);
pthread_mutex_unlock(&q->lock);
```

`msgDrop` — выставляет флаг и делает **broadcast** на обе condition-переменные:

```c
pthread_cond_broadcast(&q->not_full);
pthread_cond_broadcast(&q->not_empty);
```

Все ждущие просыпаются, проверяют флаг и выходят с `-1`. Без этого механизма потоки могли бы навечно зависнуть в `pthread_cond_wait`.

## Что важно отметить

- **`while`, а не `if`** перед `pthread_cond_wait` — защита от spurious wakeup.
- Каждое сообщение копируется **в очередь** (а не передаётся указателем), чтобы клиент мог переиспользовать буфер сразу после `msgSend`.
- `msgDrop` — фича из пункта «дополнительно» PDF, заодно она нужна для аккуратного завершения программы. Без неё `main` бы пришлось ждать клиентов бесконечно.
