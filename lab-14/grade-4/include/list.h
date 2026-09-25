#ifndef LIST_H
#define LIST_H

// описание одной пары кроссовок
typedef struct {
    char brand[20];
    char model[20];
    int  size;
    int  price;
} Sneaker;

// узел двусвязного списка.
// data — указатель на структуру (выделяется отдельно — пункт 4 задания)
// next — вперёд, prev — назад
typedef struct Node {
    Sneaker     *data; // указатель на структуру (пункт 4)
    struct Node *next;
    struct Node *prev;
} Node;

// объявления функций (реализация в list.c)
Sneaker *CreateSneaker(void);
Node    *CreateNode(void);
void     PushBack(Node **head, Node **tail);
void     PrintNode(Node *node, int idx);
void     FreeList(Node *head);

#endif
