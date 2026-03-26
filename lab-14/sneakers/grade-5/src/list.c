#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/list.h"

// Создаёт структуру Sneaker со случайными данными
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

// Создаёт узел для указанного ряда (0 или 1)
Node *CreateNode(int row) {
    Node *node  = malloc(sizeof(Node));
    node->data  = CreateSneaker();
    node->next  = NULL;
    node->cross = NULL; // сначала без вертикальных связей
    node->row   = row;
    return node;
}

// Печатает один узел с указанием ряда
void PrintNode(Node *node) {
    printf("[%s] %-10s %-10s размер: %-4d цена: $%d\n",
           node->row == 0 ? "верх" : "низ ",
           node->data->brand,
           node->data->model,
           node->data->size,
           node->data->price);
}
