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

/*
 * Схема списка:
 *
 * S → [aN] → [aN-2] → [aN-4] → ... → [a2] → nil
 *       ↕         ↕          ↕              ↕
 *     [aN-1] → [aN-3] → [aN-5] → ... → [a1] → nil
 *
 * Верхний ряд: чётные a (через next)
 * Нижний ряд: нечётные a (через next)
 * cross: верхний[i] ↔ нижний[i], узлы без пары: cross = NULL
 */
typedef struct Node {
    Room        *data;
    struct Node *next;   // вправо по ряду
    struct Node *cross;  // вверх/вниз между рядами
    int          row;    // 0 = верхний, 1 = нижний
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

Node *CreateNode(int number, int row) {
    Node *node  = malloc(sizeof(Node));
    node->data  = CreateRoom(number);
    node->next  = NULL;
    node->cross = NULL;
    node->row   = row;
    return node;
}

void PrintNode(Node *node) {
    printf("[%s] a%-3d | %-12s level:%-3d size:%d\n",
           node->row == 0 ? "верх" : "низ ",
           node->data->number,
           node->data->name,
           node->data->level,
           node->data->resolution);
}

int main(int argc, char *argv[]) {
    int N, K;
    if (argc > 2) {
        N = atoi(argv[1]);
        K = atoi(argv[2]);
    } else {
        printf("Длина верхнего ряда N: "); scanf("%d", &N);
        printf("Длина нижнего ряда K: "); scanf("%d", &K);
    }
    srand(time(NULL));

    Node *topHead = NULL, *topTail = NULL;
    for (int i = 0; i < N; i++) {
        int num = 2 * (N - i);
        Node *node = CreateNode(num, 0);
        if (!topHead) topHead = topTail = node;
        else { topTail->next = node; topTail = node; }
    }

    Node *botHead = NULL, *botTail = NULL;
    for (int i = 0; i < K; i++) {
        int num = 2 * (N - i) - 1;
        if (num < 1) num = 1;
        Node *node = CreateNode(num, 1);
        if (!botHead) botHead = botTail = node;
        else { botTail->next = node; botTail = node; }
    }

    // cross: top[i] ↔ bot[i]
    Node *t = topHead, *b = botHead;
    while (t && b) { t->cross = b; b->cross = t; t = t->next; b = b->next; }
    while (t) { t->cross = NULL; t = t->next; }
    while (b) { b->cross = NULL; b = b->next; }

    Node *topArr[1024], *botArr[1024];
    int   topLen = 0, botLen = 0;
    { Node *p = topHead; while (p) { topArr[topLen++] = p; p = p->next; } }
    { Node *p = botHead; while (p) { botArr[botLen++] = p; p = p->next; } }

    Node *cur = topHead;
    printf("\nНавигация:\n");
    printf("  D/6 — вправо, A/4 — влево, S/2 — вниз (cross), W/8 — вверх (cross)\n");
    printf("  R — вернуться к S, Q — выход\n\n");
    PrintNode(cur);

    int topIdx = 0, botIdx = 0, inBot = 0;
    char ch; int running = 1;
    while (running) {
        printf("Ввод: "); scanf(" %c", &ch);
        switch (ch) {
            case 'D': case 'd': case '6':
                if (!inBot) {
                    if (topIdx + 1 < topLen) { topIdx++; cur = topArr[topIdx]; PrintNode(cur); }
                    else { printf("Конец верхнего ряда.\n"); }
                } else {
                    if (botIdx + 1 < botLen) { botIdx++; cur = botArr[botIdx]; PrintNode(cur); }
                    else { printf("Конец нижнего ряда.\n"); }
                }
                break;
            case 'A': case 'a': case '4':
                if (!inBot) {
                    if (topIdx > 0) { topIdx--; cur = topArr[topIdx]; PrintNode(cur); }
                    else { printf("Начало верхнего ряда (S).\n"); }
                } else {
                    if (botIdx > 0) { botIdx--; cur = botArr[botIdx]; PrintNode(cur); }
                    else { printf("Начало нижнего ряда.\n"); }
                }
                break;
            case 'S': case 's': case '2':
                if (!inBot && cur->cross) { inBot = 1; botIdx = topIdx; cur = botArr[botIdx]; PrintNode(cur); }
                else if (!inBot) { printf("Переход вниз невозможен.\n"); }
                else { printf("Уже в нижнем ряду.\n"); }
                break;
            case 'W': case 'w': case '8':
                if (inBot && cur->cross) { inBot = 0; topIdx = botIdx; cur = topArr[topIdx]; PrintNode(cur); }
                else if (inBot) { printf("Переход вверх невозможен.\n"); }
                else { printf("Уже в верхнем ряду.\n"); }
                break;
            case 'R': case 'r':
                inBot = 0; topIdx = 0; cur = topArr[0];
                printf("Вернулись к S.\n"); PrintNode(cur);
                break;
            case 'Q': case 'q': running = 0; break;
            default: printf("Неизвестная команда.\n");
        }
    }
    Node *p = topHead; while (p) { Node *nx = p->next; free(p->data); free(p); p = nx; }
    p = botHead;       while (p) { Node *nx = p->next; free(p->data); free(p); p = nx; }
    return 0;
}
