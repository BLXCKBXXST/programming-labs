#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char brand[20];
    char model[20];
    int  size;
    int  price;
} Sneaker;

// узел со ссылкой на структуру (п.б4) + next/prev
typedef struct Node {
    Sneaker     *data;   // указатель на структуру (п.б4)
    struct Node *next;
    struct Node *prev;
} Node;

Sneaker *CreateSneaker(void) {
    char *brands[] = {"Nike", "Adidas", "Puma"};
    char *models[] = {"Pro", "Super", "Ultra"};
    int   prices[] = {200, 250, 300, 350, 400, 450, 500};

    Sneaker *s = malloc(sizeof(Sneaker));
    int b = rand() % 3;
    int m = rand() % 3;
    strcpy(s->brand, brands[b]);
    strcpy(s->model, models[m]);
    s->size  = 36 + rand() % 9;
    s->price = prices[rand() % 7];
    return s;
}

Node *CreateNode(void) {
    Node *node = malloc(sizeof(Node));
    node->data = CreateSneaker();  // инициализируем указатель на данные
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void PushBack(Node **head, Node **tail) {
    Node *node = CreateNode();
    if (*head == NULL) {
        *head = *tail = node;
        return;
    }
    node->prev  = *tail;
    (*tail)->next = node;
    *tail = node;
}

void PrintNode(Node *node, int idx) {
    printf("[%d] %-10s %-10s размер: %-4d цена: $%d\n",
           idx, node->data->brand, node->data->model,
           node->data->size, node->data->price);
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
    for (int i = 0; i < n; i++) PushBack(&head, &tail);

    // навигация WASD
    Node *cur = head;
    int   idx = 1;
    int   running = 1;

    printf("Навигация: D/6 - вперёд, A/4 - назад, Q - выход\n");
    printf("Текущий узел:\n");
    PrintNode(cur, idx);

    char ch;
    while (running) {
        printf("Ввод: ");
        scanf(" %c", &ch);
        switch (ch) {
            case 'D': case 'd': case '6':
                if (cur->next) { cur = cur->next; idx++; PrintNode(cur, idx); }
                else printf("Достигли конца списка. Вернуться в начало? (y/n): "), scanf(" %c", &ch), (ch=='y')?(cur=head,idx=1,PrintNode(cur,idx)):0;
                break;
            case 'A': case 'a': case '4':
                if (cur->prev) { cur = cur->prev; idx--; PrintNode(cur, idx); }
                else printf("Начало списка.\n");
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
