#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char name[50];
    int  level;
    int  number;
    int  resolution;
} Room;

// узел со ссылкой на структуру (п.У4) + next/prev
typedef struct Node {
    Room        *data;   // указатель на структуру (п.У4)
    struct Node *next;
    struct Node *prev;
} Node;

static const char *NAMES[] = {
    "Dungeon", "Crypt", "Throne", "Library", "Armory",
    "Garden",  "Cave",  "Tower",  "Vault",   "Chapel"
};

Room *CreateRoom(int number) {
    Room *r = malloc(sizeof(Room));
    strcpy(r->name,  NAMES[rand() % 10]);
    r->level      = 1 + rand() % 10;
    r->number     = number;
    r->resolution = 5 + rand() % 46;
    return r;
}

Node *CreateNode(int number) {
    Node *node = malloc(sizeof(Node));
    node->data = CreateRoom(number);  // инициализация указателя
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void PushBack(Node **head, Node **tail, int number) {
    Node *node = CreateNode(number);
    if (*head == NULL) { *head = *tail = node; return; }
    node->prev    = *tail;
    (*tail)->next = node;
    *tail         = node;
}

void PrintNode(Node *node, int idx) {
    printf("[%d] %-12s level:%-3d number:%-4d size:%d\n",
           idx, node->data->name, node->data->level,
           node->data->number,   node->data->resolution);
}

void FreeList(Node *head) {
    while (head) {
        Node *tmp = head;
        head = head->next;
        free(tmp->data);
        free(tmp);
    }
}

int main(int argc, char *argv[]) {
    int n;
    if (argc > 1) n = atoi(argv[1]);
    else { printf("n: "); scanf("%d", &n); }

    srand(time(NULL));
    Node *head = NULL, *tail = NULL;
    for (int i = 0; i < n; i++) PushBack(&head, &tail, i + 1);

    // навигация WASD
    Node *cur = head;  // S = начало списка
    int   idx = 1;
    printf("Навигация: D/6 — вперёд, A/4 — назад, Q — выход\n");
    printf("Текущая комната (S):\n");
    PrintNode(cur, idx);

    char ch;
    int  running = 1;
    while (running) {
        printf("Ввод: ");
        scanf(" %c", &ch);
        switch (ch) {
            case 'D': case 'd': case '6':
                if (cur->next) {
                    cur = cur->next; idx++;
                    PrintNode(cur, idx);
                } else {
                    printf("Достигли конца списка. Вернуться в начало (S)? (y/n): ");
                    scanf(" %c", &ch);
                    if (ch == 'y') { cur = head; idx = 1; PrintNode(cur, idx); }
                }
                break;
            case 'A': case 'a': case '4':
                if (cur->prev) {
                    cur = cur->prev; idx--;
                    PrintNode(cur, idx);
                } else {
                    printf("Вы уже в начале списка (S).\n");
                }
                break;
            case 'Q': case 'q':
                running = 0;
                break;
            default:
                printf("Неизвестная команда.\n");
        }
    }
    FreeList(head);
    return 0;
}
