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

/*
 * Схема списка:
 *
 * S → [a1] → [a3] → [a5] → ... → [aN-1] → nil
 *       ↓       ↓     ↓               ↓
 *     [a2]  ← [a4] ← [a6] ← ... ← [aN]
 *     nil      nil    nil            nil
 *
 * верхний ряд: next → вправо
 * нижний ряд:  next → влево
 * cross: верхний[i] ↔ нижний[i], NULL если без пары
 */
typedef struct Node {
    Sneaker     *data;
    struct Node *next;   // верхний: вправо | нижний: влево
    struct Node *cross;  // вверх/вниз
    int          row;    // 0 = верхний, 1 = нижний
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

int main(int argc, char *argv[]) {
    int N, K;
    if (argc > 2) { N = atoi(argv[1]); K = atoi(argv[2]); }
    else {
        printf("Длина верхнего ряда N: "); scanf("%d", &N);
        printf("Длина нижнего ряда K: "); scanf("%d", &K);
    }
    srand(time(NULL));

    // верхний ряд: N узлов, next → вправо
    Node *topHead = NULL, *topTail = NULL;
    for (int i = 0; i < N; i++) {
        Node *node = CreateNode(0);
        if (!topHead) topHead = topTail = node;
        else { topTail->next = node; topTail = node; }
    }

    // нижний ряд: K узлов, каждый новый в начало (незначит next → влево)
    Node *botHead = NULL, *botTail = NULL;
    for (int i = 0; i < K; i++) {
        Node *node = CreateNode(1);
        node->next = botHead;
        botHead = node;
        if (!botTail) botTail = node;
    }

    // собираем нижний ряд слева направо в массив
    Node **bot = malloc(K * sizeof(Node *));
    Node *cur  = botTail;
    for (int i = K - 1; i >= 0; i--) { bot[i] = cur; cur = cur->next; }

    // cross: top[i] ↔ bot[i]
    Node *t = topHead;
    for (int i = 0; i < N && i < K; i++) {
        t->cross  = bot[i];
        bot[i]->cross = t;
        t = t->next;
    }
    while (t) { t->cross = NULL; t = t->next; }
    for (int i = (N < K ? N : K); i < K; i++) bot[i]->cross = NULL;
    free(bot);

    cur = topHead;
    printf("\nНавигация:\n");
    printf("  D/6 — вправо, A/4 — назад, S/2 — вниз (cross), W/8 — вверх (cross)\n");
    printf("  R — к S, Q — выход\n\n");
    PrintNode(cur);

    char ch; int running = 1;
    while (running) {
        printf("Ввод: "); scanf(" %c", &ch);
        switch (ch) {
            case 'D': case 'd': case '6':
                if (cur->row == 0) {
                    if (cur->next) { cur = cur->next; PrintNode(cur); }
                    else { printf("Конец верхнего ряда.\n"); }
                } else {
                    if (cur->cross && cur->cross->next && cur->cross->next->cross) { cur = cur->cross->next->cross; PrintNode(cur); }
                    else printf("Конец нижнего ряда.\n");
                }
                break;
            case 'A': case 'a': case '4':
                if (cur->row == 0) {
                    if (cur == topHead) { printf("Начало (S).\n"); break; }
                    Node *p = topHead; while (p->next && p->next != cur) p = p->next;
                    cur = p; PrintNode(cur);
                } else {
                    if (cur->next) { cur = cur->next; PrintNode(cur); }
                    else printf("Левый край нижнего ряда.\n");
                }
                break;
            case 'S': case 's': case '2':
                if (cur->row == 0 && cur->cross) { cur = cur->cross; PrintNode(cur); }
                else if (cur->row == 0) printf("Переход вниз невозможен.\n");
                else printf("Уже в нижнем ряду.\n");
                break;
            case 'W': case 'w': case '8':
                if (cur->row == 1 && cur->cross) { cur = cur->cross; PrintNode(cur); }
                else if (cur->row == 1) printf("Переход вверх невозможен.\n");
                else printf("Уже в верхнем ряду.\n");
                break;
            case 'R': case 'r':
                cur = topHead; printf("Вернулись к S.\n"); PrintNode(cur); break;
            case 'Q': case 'q': running = 0; break;
            default: printf("Неизвестная команда.\n");
        }
    }
    Node *p = topHead; while (p) { Node *nx=p->next; free(p->data); free(p); p=nx; }
    p = botHead;       while (p) { Node *nx=p->next; free(p->data); free(p); p=nx; }
    return 0;
}
