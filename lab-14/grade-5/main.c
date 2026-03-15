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

// узел зигзагообразного списка (вариант со схемы):
// next  - вправо в своём ряду
// cross - вниз (из верхнего) или вверх (из нижнего)
typedef struct Node {
    Sneaker     *data;
    struct Node *next;   // вправо
    struct Node *cross;  // верх/вниз
    int          row;    // 0 = верхний ряд, 1 = нижний
} Node;

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
    Node *n  = malloc(sizeof(Node));
    n->data  = CreateSneaker();
    n->next  = NULL;
    n->cross = NULL;
    n->row   = row;
    return n;
}

void PrintNode(Node *node) {
    printf("[%s] %-10s %-10s размер: %-3d цена: $%d\n",
           node->row == 0 ? "верх" : "низ ",
           node->data->brand, node->data->model,
           node->data->size,  node->data->price);
}

void FreeRow(Node *head) {
    while (head) {
        Node *tmp = head;
        head = head->next;
        free(tmp->data);
        free(tmp);
    }
}

int main(int argc, char *argv[]) {
    int N, K;
    if (argc > 2) { N = atoi(argv[1]); K = atoi(argv[2]); }
    else {
        printf("Длина верхнего ряда N: "); scanf("%d", &N);
        printf("Длина нижнего ряда K: "); scanf("%d", &K);
    }
    srand(time(NULL));

    // строим верхний ряд (a1, a3, a5... — нечётные по позиции)
    Node *topHead = NULL, *topTail = NULL;
    for (int i = 0; i < N; i++) {
        Node *node = CreateNode(0);
        if (!topHead) topHead = topTail = node;
        else { topTail->next = node; topTail = node; }
    }

    // строим нижний ряд (a2, a4, a6... — идут в обратном порядке)
    Node *botHead = NULL, *botTail = NULL;
    for (int i = 0; i < K; i++) {
        Node *node = CreateNode(1);
        if (!botHead) botHead = botTail = node;
        else { botTail->next = node; botTail = node; }
    }

    // проставляем cross-указатели (верх <-> низ)
    // если один ряд длиннее - лишним cross = NULL (п.б7)
    Node *t = topHead, *b = botHead;
    while (t && b) {
        t->cross = b;
        b->cross = t;
        t = t->next;
        b = b->next;
    }
    // оставшиеся узлы выходящего за короткий - cross = NULL
    while (t) { t->cross = NULL; t = t->next; }
    while (b) { b->cross = NULL; b = b->next; }

    // начинаем с S (верхний ряд, первый элемент)
    Node *cur = topHead;
    printf("Навигация: D/6 - вправо, A/4 - назад, S/2 - вниз, W/8 - вверх, R - в начало, Q - выход\n");
    printf("Текущий:\n");
    PrintNode(cur);

    char ch;
    int  running = 1;
    while (running) {
        printf("Ввод: ");
        scanf(" %c", &ch);
        switch (ch) {
            case 'D': case 'd': case '6':
                if (cur->next) { cur = cur->next; PrintNode(cur); }
                else {
                    printf("Конец ряда. Вернуться к S? (y/n): ");
                    scanf(" %c", &ch);
                    if (ch == 'y') { cur = topHead; PrintNode(cur); }
                }
                break;
            case 'A': case 'a': case '4':
                // для навигации назад ищем prev через cross-цепочку (проходимся от S)
                {
                    Node *row = (cur->row == 0) ? topHead : botHead;
                    if (row == cur) { printf("Начало ряда.\n"); break; }
                    Node *prev = row;
                    while (prev->next && prev->next != cur) prev = prev->next;
                    if (prev->next == cur) { cur = prev; PrintNode(cur); }
                    else printf("Начало ряда.\n");
                }
                break;
            case 'S': case 's': case '2':
                if (cur->row == 0 && cur->cross) { cur = cur->cross; PrintNode(cur); }
                else if (cur->row == 0) printf("Нижний ряд короче, переход невозможен.\n");
                else printf("Вы уже в нижнем ряду.\n");
                break;
            case 'W': case 'w': case '8':
                if (cur->row == 1 && cur->cross) { cur = cur->cross; PrintNode(cur); }
                else if (cur->row == 1) printf("Верхний ряд короче, переход невозможен.\n");
                else printf("Вы уже в верхнем ряду.\n");
                break;
            case 'R': case 'r':
                cur = topHead; printf("Вернулись к S.\n"); PrintNode(cur);
                break;
            case 'Q': case 'q':
                running = 0;
                break;
            default:
                printf("Неизвестная команда.\n");
        }
    }

    FreeRow(topHead);
    FreeRow(botHead);
    return 0;
}
