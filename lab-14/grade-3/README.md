# Lab 14 — sneakers — Оценка 3

## Что реализовано

### Односвязный список узлов Sneaker

```c
typedef struct Node {
    Sneaker      data;   // данные внутри узла (не указатель)
    struct Node *next;
} Node;
```

### Функции

- `CreateNode()` — `malloc` + случайные brand/model/size/price
- `PushBack(&head)` — добавляет узел в конец списка
- `PrintList(head)` — выводит таблицу
- `FreeList(head)` — очищает память

### `n` через `argv[1]`

```bash
./sneakers 10    # 10 узлов
./sneakers       # ввод через scanf
```

## Сборка

```bash
gcc -Wall main.c -o sneakers && ./sneakers 10
```
