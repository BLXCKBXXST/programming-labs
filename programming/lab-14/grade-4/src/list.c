#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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

Node *CreateNode(void) {
    Node *node = malloc(sizeof(Node));
    node->data = CreateSneaker();
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void PushBack(Node **head, Node **tail) {
    Node *node = CreateNode();

    if (*head == NULL) {
        *head = node;
        *tail = node;
        return;
    }

    node->prev    = *tail;
    (*tail)->next = node;
    *tail = node;
}

void PrintNode(Node *node, int idx) {
    printf("[%d] %-10s %-10s размер: %-4d цена: $%d\n",
           idx,
           node->data->brand,
           node->data->model,
           node->data->size,
           node->data->price);
}

// Освобождает всю память списка.
// Узел и структура Sneaker — две разные области памяти.
void FreeList(Node *head) {
    while (head != NULL) {
        Node *tmp = head;
        head = head->next;
        free(tmp->data);
        free(tmp);
    }
}
