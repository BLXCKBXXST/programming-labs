# Lab 14 — katysha-roguelike — Оценка 3

## Что реализовано

### Односвязный список узлов Room

```c
typedef struct Node {
    Room         data;   // данные внутри узла (не указатель)
    struct Node *next;   // указатель на следующий узел
} Node;
```

### Функции

- `CreateNode(number)` — создаёт узел: `malloc` + случайные данные
- `PushBack(&head, n)` — добавляет узел в конец списка
- `PrintList(head)` — выводит список в виде таблицы
- `FreeList(head)` — очищает всю динамически выделенную память

### `n` через `argv[1]`

```bash
./rooms 10    # создать 10 комнат
./rooms       # ввод через scanf
```

## Сборка и запуск

```bash
gcc -Wall main.c -o rooms
./rooms 10
```
