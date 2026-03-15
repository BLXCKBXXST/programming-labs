# Lab 14 — sneakers — Оценка 3

## Что реализовано

Всё в одном файле `main.c`.

### 1. Структура узла односвязного списка

Данные узла — структура `Sneaker` из лабы 12.

```c
typedef struct {
    char brand[20];
    char model[20];
    int  size;
    int  price;
} Sneaker;

typedef struct Node {
    Sneaker      data;   // данные хранятся внутри узла
    struct Node *next;   // указатель на следующий узел
} Node;
```

### 2. Функции

- `CreateNode()` — создаёт узел со случайными осмысленными данными (`malloc`, `rand`)
- `PushBack(Node **head)` — добавляет узел в конец списка: проходит до последнего узла и присваивает `cur->next`
- `PrintList(Node *head)` — выводит весь список в виде таблицы (бренд, модель, размер, цена)
- `FreeList(Node *head)` — освобождает всю память списка

### 3. Создание списка из N элементов

N можно задать двумя способами:

```bash
./sneakers 10        # через аргумент main
./sneakers           # ввод с клавиатуры
```

## Сборка и запуск

```bash
gcc -Wall main.c -o sneakers
./sneakers 10
```
