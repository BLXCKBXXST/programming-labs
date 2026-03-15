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
 * Верхний ряд: чётные a (aN, aN-2, ..., a2), next → вправо
 * Нижний ряд: нечётные a (aN-1, aN-3, ..., a1), next → вправо
 * cross: верхний[i] ↔ нижний[i]
 * Узлы длинного ряда без пары: cross = NULL
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
        printf("Длина верхнего ряда N (чётные a): "); scanf("%d", &N);
        printf("Длина нижнего ряда K (нечётные a): "); scanf("%d", &K);
    }
    srand(time(NULL));

    /*
     * Верхний ряд: N узлов
     * По схеме: aN, aN-2, ..., a2  (чётные индексы в обратном порядке)
     * Номеруем: верх[0]=aN, верх[1]=aN-2, ..., верх[N-1]=a2
     * Для наглядности просто пронумеруем через один, начиная с 2*N
     */
    Node *topHead = NULL, *topTail = NULL;
    for (int i = 0; i < N; i++) {
        // чётные номера: 2*N, 2*N-2, ..., 2
        int num = 2 * (N - i);
        Node *node = CreateNode(num, 0);
        if (!topHead) topHead = topTail = node;
        else { topTail->next = node; topTail = node; }
    }

    /*
     * Нижний ряд: K узлов
     * По схеме: aN-1, aN-3, ..., a1 (нечётные индексы в обратном порядке)
     * Для наглядности просто пронумеруем через один, начиная с 2*N-1
     */
    Node *botHead = NULL, *botTail = NULL;
    for (int i = 0; i < K; i++) {
        // нечётные номера: 2*N-1, 2*N-3, ..., 1
        int num = 2 * (N - i) - 1;
        if (num < 1) num = 1;  // не выходим за пределы
        Node *node = CreateNode(num, 1);
        if (!botHead) botHead = botTail = node;
        else { botTail->next = node; botTail = node; }
    }

    // проставляем cross: top[i] ↔ bot[i]
    Node *t = topHead, *b = botHead;
    while (t && b) {
        t->cross = b;
        b->cross = t;
        t = t->next;
        b = b->next;
    }
    // остаток длинного ряда — cross = NULL (п.У7)
    while (t) { t->cross = NULL; t = t->next; }
    while (b) { b->cross = NULL; b = b->next; }

    // навигация
    Node *cur = topHead;
    printf("\nНавигация:\n");
    printf("  D/6 — вправо по ряду\n");
    printf("  A/4 — влево по ряду\n");
    printf("  S/2 — вниз (cross)\n");
    printf("  W/8 — вверх (cross)\n");
    printf("  R   — вернуться к S (начало)\n");
    printf("  Q   — выход\n\n");
    printf("Текущая комната (S):\n");
    PrintNode(cur);

    // для навигации назад храним prev-ссылки в виде массивов (O(1) проход)
    Node *topArr[1024], *botArr[1024];
    int   topLen = 0, botLen = 0;
    { Node *p = topHead; while (p) { topArr[topLen++] = p; p = p->next; } }
    { Node *p = botHead; while (p) { botArr[botLen++] = p; p = p->next; } }

    int topIdx = 0, botIdx = -1;  // -1 если мы в верхнем ряду
    int inBot = 0;  // 0 — верхний, 1 — нижний

    char ch;
    int  running = 1;
    while (running) {
        printf("Ввод: ");
        scanf(" %c", &ch);
        switch (ch) {
            case 'D': case 'd': case '6':
                if (!inBot) {
                    if (topIdx + 1 < topLen) {
                        topIdx++; cur = topArr[topIdx];
                        PrintNode(cur);
                    } else {
                        printf("Конец верхнего ряда. Вернуться к S? (y/n): ");
                        char c; scanf(" %c", &c);
                        if (c == 'y') { topIdx = 0; cur = topArr[0]; PrintNode(cur); }
                    }
                } else {
                    if (botIdx + 1 < botLen) {
                        botIdx++; cur = botArr[botIdx];
                        PrintNode(cur);
                    } else {
                        printf("Конец нижнего ряда. Вернуться к S? (y/n): ");
                        char c; scanf(" %c", &c);
                        if (c == 'y') { inBot = 0; topIdx = 0; cur = topArr[0]; PrintNode(cur); }
                    }
                }
                break;

            case 'A': case 'a': case '4':
                if (!inBot) {
                    if (topIdx > 0) {
                        topIdx--; cur = topArr[topIdx];
                        PrintNode(cur);
                    } else {
                        printf("Вы уже в начале верхнего ряда (S).\n");
                    }
                } else {
                    if (botIdx > 0) {
                        botIdx--; cur = botArr[botIdx];
                        PrintNode(cur);
                    } else {
                        printf("Вы уже в начале нижнего ряда.\n");
                    }
                }
                break;

            case 'S': case 's': case '2':
                if (!inBot) {
                    if (cur->cross) {
                        inBot  = 1;
                        botIdx = topIdx;  // i-й узел верхнего → i-й узел нижнего
                        cur    = botArr[botIdx];
                        PrintNode(cur);
                    } else {
                        printf("Переход вниз невозможен: нижний ряд короче.\n");
                    }
                } else {
                    printf("Вы уже в нижнем ряду.\n");
                }
                break;

            case 'W': case 'w': case '8':
                if (inBot) {
                    if (cur->cross) {
                        inBot  = 0;
                        topIdx = botIdx;
                        cur    = topArr[topIdx];
                        PrintNode(cur);
                    } else {
                        printf("Переход вверх невозможен: верхний ряд короче.\n");
                    }
                } else {
                    printf("Вы уже в верхнем ряду.\n");
                }
                break;

            case 'R': case 'r':
                inBot = 0; topIdx = 0;
                cur = topArr[0];
                printf("Вернулись к S.\n");
                PrintNode(cur);
                break;

            case 'Q': case 'q':
                running = 0;
                break;

            default:
                printf("Неизвестная команда.\n");
        }
    }

    // освобождение памяти
    Node *p = topHead;
    while (p) { Node *nx = p->next; free(p->data); free(p); p = nx; }
    p = botHead;
    while (p) { Node *nx = p->next; free(p->data); free(p); p = nx; }

    return 0;
}
