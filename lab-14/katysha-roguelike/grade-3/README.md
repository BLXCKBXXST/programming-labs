# Lab 14 — katysha-roguelike — Оценка 3

## Что реализовано

Всё в одном файле `main.c`.

### 1. Структура узла односвязного списка

Данные узла — структура `Room` из лабы 12:

```c
typedef struct {
    char name[50];    // имя комнаты
    int  level;       // уровень/сложность
    int  number;      // номер комнаты
    int  resolution;  // размер комнаты
} Room;

typedef struct Node {
    Room         data;   // данные хранятся внутри узла
    struct Node *next;   // указатель на следующий узел
} Node;
```

### 2. Функции

- `CreateNode(int number)` — создаёт узел со случайными осмысленными данными:
  - `name` — из набора 10 названий: Dungeon, Crypt, Throne и др.
  - `level` — диапазон `[1..10]`
  - `number` — порядковый номер
  - `resolution` — диапазон `[5..50]`
- `PushBack(Node **head, int number)` — добавляет узел в конец списка
- `PrintList(Node *head)` — выводит весь список в виде таблицы
- `FreeList(Node *head)` — освобождает всю память

### 3. Создание списка из N элементов

N можно задать двумя способами:

```bash
./rooms 10        # через аргумент main
./rooms           # ввод с клавиатуры
```

## Сборка и запуск

```bash
gcc -Wall main.c -o rooms
./rooms 10
```
