#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ---- структура данных ----
typedef struct {
    char brand[20];
    char model[20];
    int  size;
    int  price;
} Sneaker;

// ---- узел односвязного списка ----
typedef struct Node {
    Sneaker      data;   // данные внутри узла (не указатель)
    struct Node *next;
} Node;

Node *CreateNode(void) {
    char *brands[] = {"Nike", "Adidas", "Puma"};
    char *models[] = {"Pro", "Super", "Ultra"};
    int   prices[] = {200, 250, 300, 350, 400, 450, 500};
    Node *node = malloc(sizeof(Node));
    int b = rand() % 3, m = rand() % 3;
    strcpy(node->data.brand, brands[b]);
    strcpy(node->data.model, models[m]);
    node->data.size  = 36 + rand() % 9;
    node->data.price = prices[rand() % 7];
    node->next = NULL;
    return node;
}

void PushBack(Node **head) {
    Node *node = CreateNode();
    if (*head == NULL) { *head = node; return; }
    Node *cur = *head;
    while (cur->next) cur = cur->next;
    cur->next = node;
}

void PrintList(Node *head) {
    printf("\n%-5s %-10s %-10s %-8s %s\n",
           "№", "Бренд", "Модель", "Размер", "Цена");
    printf("─────────────────────────────────────────────\n");
    int i = 1;
    while (head) {
        printf("%-5d %-10s %-10s %-8d $%d\n",
               i++, head->data.brand, head->data.model,
               head->data.size, head->data.price);
        head = head->next;
    }
}

void FreeList(Node *head) {
    while (head) { Node *tmp = head; head = head->next; free(tmp); }
}

int main(int argc, char *argv[]) {
    int n;
    if (argc > 1) n = atoi(argv[1]);
    else { printf("Введите n: "); scanf("%d", &n); }
    srand(time(NULL));
    Node *head = NULL;
    for (int i = 0; i < n; i++) PushBack(&head);
    printf("Односвязный список (%d элементов):", n);
    PrintList(head);
    FreeList(head);
    return 0;
}
