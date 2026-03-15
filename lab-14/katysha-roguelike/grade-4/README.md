# Lab 14 — katysha-roguelike — Оценка 4

## Что реализовано

### Двусвязный список + узел хранит указатель `Room*`

```c
typedef struct Node {
    Room        *data;   // указатель на отдельно выделенную Room
    struct Node *next;   // вперёд
    struct Node *prev;   // назад
} Node;
```

### Навигация WASD

| Клавиша | Действие |
|---|---|
| `D` / `6` | вперёд (`cur->next`) |
| `A` / `4` | назад (`cur->prev`) |
| `Q` | выход |

При достижении конца предлагает вернуться на `S` (начало).

## Сборка и запуск

```bash
gcc -Wall main.c -o rooms
./rooms 10
```
