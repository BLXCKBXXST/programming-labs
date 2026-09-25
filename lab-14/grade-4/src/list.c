#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/list.h"

// Создаёт структуру Sneaker, заполненную случайными данными
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

// Создаёт узел и инициализирует указатель data (пункт 4)
Node *CreateNode(void) {
    Node *node = malloc(sizeof(Node));
    node->data = CreateSneaker(); // инициализируем указатель на структуру
    node->next = NULL;
    node->prev = NULL;
    return node;
}

// Добавляет узел в конец двусвязного списка
void PushBack(Node **head, Node **tail) {
    Node *node = CreateNode();

    if (*head == NULL) {
        *head = node;
        *tail = node;
        return;
    }

    // новый узел смотрит назад на старый хвост
    node->prev    = *tail;
    // старый хвост смотрит вперёд на новый
    (*tail)->next = node;
    // обновляем хвост
    *tail = node;
}

// Печатает информацию об одном узле
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
        free(tmp->data); // сначала освобождаем структуру Sneaker
        free(tmp);       // потом сам узел
    }
}
