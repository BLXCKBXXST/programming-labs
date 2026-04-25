#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/list.h"

Sneaker *CreateSneaker(void) {
    char *brands[] = {"Nike", "Adidas", "Puma"};
    char *models[] = {"Pro", "Super", "Ultra"};
    int   prices[] = {200, 250, 300, 350, 400, 450, 500};
    Sneaker *s = malloc(sizeof(Sneaker));
    strcpy(s->brand, brands[rand() % 3]);
    strcpy(s->model, models[rand() % 3]);
    s->size  = 36 + rand() % 9;
    s->price = prices[rand() % 7];
    return s;
}

Node *CreateNode(int row) {
    Node *node  = malloc(sizeof(Node));
    node->data  = CreateSneaker();
    node->next  = NULL;
    node->prev  = NULL;
    node->cross = NULL;
    node->row   = row;
    node->idx   = -1; // заполняется после построения цепи
    return node;
}

void PrintNode(Node *node) {
    // по схеме: top[i] = a_(N-2i), bot[i] = a_(N-1-2i)
    // но поскольку N неизвестно здесь, просто показываем ряд и индекс
    printf("[%s #%d] %-8s %-8s размер:%-3d цена:$%d  cross:%s\n",
           node->row == 0 ? "верх" : "низ ",
           node->idx,
           node->data->brand,
           node->data->model,
           node->data->size,
           node->data->price,
           node->cross ? "yes" : "nil");
}
