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
 *  S → [1] → [2] → [3] → ... → [N] → NULL   (верхний ряд, next → вправо)
 *       |      |     |
 *      [1] ← [2] ← [3] ← ... ← [K] → NULL  (нижний ряд, next → влево)
 *      [1] → [2] → [3] → ... → [K] → NULL  (нижний ряд, prev → вправо)
 *
 * cross — вертикальная связь между рядами.
 * prev  — предыдущий узел (для верхнего: влево; для нижнего: вправо).
 * Если списки разной длины — cross у лишних узлов = NULL (пункт 7).
 */
typedef struct Node {
    Sneaker     *data;  // указатель на данные
    struct Node *next;  // вправо (верх) / влево (низ)
    struct Node *prev;  // влево (верх) / вправо (низ)
    struct Node *cross; // вертикальная связь (верх ↔ низ)
    int          row;   // 0 = верхний ряд, 1 = нижний ряд
} Node;

// объявления функций (реализация в list.c)
Sneaker *CreateSneaker(void);
Node    *CreateNode(int row);
void     PrintNode(Node *node);

#endif
