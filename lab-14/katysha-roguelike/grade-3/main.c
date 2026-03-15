#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ---- структура данных (из лабы 12) ----
typedef struct {
    char name[50];
    int  level;
    int  number;
    int  resolution;
} Room;

// ---- узел односвязного списка ----
typedef struct Node {
    Room         data;   // данные хранятся внутри узла
    struct Node *next;   // указатель на следующий узел
} Node;

static const char *NAMES[] = {
    "Dungeon", "Crypt", "Throne", "Library", "Armory",
    "Garden",  "Cave",  "Tower",  "Vault",   "Chapel"
};

Node *CreateNode(int number) {
    Node *node = malloc(sizeof(Node));
    strcpy(node->data.name,  NAMES[rand() % 10]);
    node->data.level      = 1 + rand() % 10;
    node->data.number     = number;
    node->data.resolution = 5 + rand() % 46;
    node->next = NULL;
    return node;
}

void PushBack(Node **head, int number) {
    Node *node = CreateNode(number);
    if (*head == NULL) { *head = node; return; }
    Node *cur = *head;
    while (cur->next) cur = cur->next;
    cur->next = node;
}

void PrintList(Node *head) {
    printf("\n%-5s %-12s %-8s %-8s %s\n",
           "№", "Название", "Уровень", "Номер", "Размер");
    printf("─────────────────────────────────────────────\n");
    int i = 1;
    while (head) {
        printf("%-5d %-12s %-8d %-8d %d\n",
               i++, head->data.name, head->data.level,
               head->data.number, head->data.resolution);
        head = head->next;
    }
}

void FreeList(Node *head) {
    while (head) { Node *tmp = head; head = head->next; free(tmp); }
}

int main(int argc, char *argv[]) {
    int n;
    if (argc > 1) {
        n = atoi(argv[1]);
    } else {
        printf("Введите количество комнат n: ");
        scanf("%d", &n);
    }
    srand(time(NULL));
    Node *head = NULL;
    for (int i = 0; i < n; i++) PushBack(&head, i + 1);
    printf("Односвязный список (%d комнат):", n);
    PrintList(head);
    FreeList(head);
    return 0;
}
