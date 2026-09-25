#ifndef LIST_H
#define LIST_H

typedef struct {
    char brand[20];
    char model[20];
    int  size;
    int  price;
} Sneaker;

/*
 * Схема (Вариант 5):
 *
 *  S → [top0:a_n] → [top1:a_n-2] → ... → [top(N-1):a_2] → NULL
 *          |               |
 *       [bot0:a_n-1] → [bot1:a_n-3] → ... → [bot(K-1):a_1] → NULL
 *           nil ← левый поинтер, next → вправо
 *
 * idx   — порядковый номер узла в своём ряду (0-базированный)
 * cross — вертикальная связь между рядами
 * Если N != K — cross у лишних узлов = NULL
 */
typedef struct Node {
    Sneaker     *data;
    struct Node *next;  // вправо (верх) / вправо (низ)
    struct Node *prev;  // влево  (верх) / NULL у левого края
    struct Node *cross;
    int          row;   // 0 = верх, 1 = низ
    int          idx;   // позиция в ряду (0-базированная)
} Node;

Sneaker *CreateSneaker(void);
Node    *CreateNode(int row);
void     PrintNode(Node *node);

#endif
