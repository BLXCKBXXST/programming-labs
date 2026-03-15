# Lab 14 — sneakers — Оценка 4

## Что реализовано

### Двусвязный список + узел хранит указатель `Sneaker*`

```c
typedef struct Node {
    Sneaker     *data;   // указатель на отдельно выделенную Sneaker
    struct Node *next;
    struct Node *prev;
} Node;
```

### Навигация WASD

| Клавиша | Действие |
|---|---|
| `D` / `6` | вперёд (`cur->next`) |
| `A` / `4` | назад (`cur->prev`) |
| `Q` | выход |

## Сборка

```bash
gcc -Wall main.c -o sneakers && ./sneakers 10
```
