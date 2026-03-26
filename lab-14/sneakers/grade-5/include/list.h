#ifndef LIST_H
#define LIST_H

// описание одной пары кроссовок
typedef struct {
    char brand[20];
    char model[20];
    int  size;
    int  price;
} Sneaker;

/*
 * Схема структуры (Вариант 1):
 *
 *  S → [1] → [2] → [3] → ... → [N] → NULL   (верхний ряд, слева направо)
 *       |      |     |
 *      [1] ← [2] ← [3] ← ... ← [K] → NULL  (нижний ряд, справа налево)
 *
 * cross — вертикальная связь между рядами.
 * Если списки разной длины — cross у лишних узлов = NULL (пункт 7).
 */
typedef struct Node {
    Sneaker     *data;  // указатель на данные
    struct Node *next;  // следующий в своём ряду
    struct Node *cross; // вертикальная связь (верх ↔ низ)
    int          row;   // 0 = верхний ряд, 1 = нижний ряд
} Node;

// объявления функций (реализация в list.c)
Sneaker *CreateSneaker(void);
Node    *CreateNode(int row);
void     PrintNode(Node *node);

#endif
