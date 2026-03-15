# Lab 12 — katysha-roguelike — Оценка 3

## Что реализовано

Всё находится в одном файле `main.c`.

### 1. Структура данных Room

```c
typedef struct {
    char name[50];   // имя комнаты
    int  level;      // уровень/сложность комнаты [1..10]
    int  number;     // номер комнаты
    int  resolution; // размер комнаты [5..50]
} Room;
```

### 2. Функции

- `FillRooms(Room rooms[N])` — заполняет массив случайными осмысленными данными (`rand`, `srand(time(NULL))`)
- `PrintRooms(Room rooms[N])` — выводит все поля в виде таблицы
- `BubbleSortByLevel(Room rooms[N])` — сортировка пузырьком по полю `level`, O(n²)

### 3. Массив и запуск

```c
#define N 100
Room rooms[N];  // статический массив
```

До и после сортировки массив выводится на экран.

## Сборка и запуск

```bash
gcc -Wall main.c -o rooms
./rooms
```
