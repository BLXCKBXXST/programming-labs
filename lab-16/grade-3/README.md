# Оценка 3 — Знакомство с pthread

Шесть упражнений, в которых используются основные API POSIX threads.

## Файлы

| # | Файл | Что делает | Ключевые API |
|---|---|---|---|
| 1 | [ex1_create.c](ex1_create.c) | Создаёт один поток, родитель и ребёнок печатают по 5 строк параллельно | `pthread_create` |
| 2 | [ex2_join.c](ex2_join.c) | Родитель сначала ждёт ребёнка, потом печатает свои строки | `pthread_join` |
| 3 | [ex3_args.c](ex3_args.c) | 4 потока с одной функцией, каждый получает свою структуру с массивом строк | передача параметра через `void *arg` |
| 4 | [ex4_cancel.c](ex4_cancel.c) | 3 потока в бесконечном цикле, через 2 сек основной их отменяет | `pthread_cancel`, точки отмены |
| 5 | [ex5_cleanup.c](ex5_cleanup.c) | + cleanup-функция, печатает «прощальное» сообщение | `pthread_cleanup_push`/`_pop` |
| 6 | [ex6_sleepsort.c](ex6_sleepsort.c) | Sleepsort O(N) — поток на каждый элемент, спит `value × 50ms` | `pthread_create`, `usleep` |

## Сборка и запуск

```bash
make all
./ex1_create
./ex2_join
./ex3_args
./ex4_cancel
./ex5_cleanup
./ex6_sleepsort                    # дефолтный массив
./ex6_sleepsort 5 2 8 1 3          # свой массив через аргументы
make clean
```

## Ожидаемые наблюдения

- **ex1 vs ex2**: в ex1 вывод parent/child перемешан, в ex2 — строго сначала весь child, потом parent.
- **ex3**: строки `[A]…`, `[B]…`, `[C]…`, `[D]…` идут в случайном порядке (тома потоки соревнуются за вывод).
- **ex4**: каждый поток успевает напечатать `tick 0` и `tick 1`, иногда `tick 2`, затем «cancelling».
- **ex5**: после отмены каждого потока появляется строка `cleanup — saying goodbye` от его cleanup-функции.
- **ex6**: вывод **отсортирован**: `1 2 3 5 8`. Чем больше значение, тем позже поток просыпается.

## Полезные флаги при сборке

```bash
gcc -Wall -Wextra -std=c11 -g -fsanitize=thread -lpthread ex2_join.c -o /tmp/ex2
./tmp/ex2
```

ThreadSanitizer ловит data race'ы, blocked-обращения к мьютексам и неинициализированные синхронизации.
