#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/list.h"

// главная функция — строит двухрядную структуру и запускает навигацию
int main(int argc, char *argv[]) {
    int N = 0, K = 0;

    if (argc > 2) {
        N = atoi(argv[1]);
        K = atoi(argv[2]);
    } else {
        printf("Длина верхнего ряда N: ");
        scanf("%d", &N);
        printf("Длина нижнего  ряда K: ");
        scanf("%d", &K);
    }

    srand(time(NULL));

    // --- строим верхний ряд (next → вправо, prev → влево) ---
    Node *S       = NULL;
    Node *topTail = NULL;
    for (int i = 0; i < N; i++) {
        Node *node = CreateNode(0);
        if (S == NULL) {
            S = node;
            topTail = node;
        } else {
            topTail->next = node;
            node->prev    = topTail;
            topTail       = node;
        }
    }

    // --- строим нижний ряд
    // next → влево (как по заданию: добавляем в начало)
    // prev → вправо (новый узел становится правее старого) ---
    Node *botHead = NULL; // левый край
    Node *botTail = NULL; // правый край
    for (int i = 0; i < K; i++) {
        Node *node  = CreateNode(1);
        node->next  = botHead;   // next → влево
        if (botHead != NULL)
            botHead->prev = node; // старый botHead.prev → вправо (на node)
        botHead = node;
        if (botTail == NULL)
            botTail = node;       // первый добавленный = правый край
    }

    // заполняем bot[] через botHead (next → влево)
    Node **bot = malloc(K * sizeof(Node *));
    Node *cur  = botHead;
    for (int i = 0; i < K; i++) {
        bot[i] = cur;
        cur    = cur->next;
    }

    // расставляем cross
    int minLen = (N < K) ? N : K;
    Node *t = S;
    for (int i = 0; i < minLen; i++) {
        t->cross      = bot[i];
        bot[i]->cross = t;
        t = t->next;
    }
    free(bot);

    // --- навигация ---
    cur = S;
    int running = 1;
    char ch;
    printf("\nНавигация:\n");
    printf("  D/6 — вправо,  A/4 — влево\n");
    printf("  S/2 — вниз (cross),  W/8 — вверх (cross)\n");
    printf("  R — к S,  Q — выход\n\n");
    PrintNode(cur);

    while (running) {
        printf("Ввод: ");
        scanf(" %c", &ch);

        if (ch == 'D' || ch == 'd' || ch == '6') {
            if (cur->row == 0) {
                // верхний ряд: вправо = next
                if (cur->next) { cur = cur->next; PrintNode(cur); }
                else printf("Конец верхнего ряда.\n");
            } else {
                // нижний ряд: вправо = prev
                if (cur->prev) { cur = cur->prev; PrintNode(cur); }
                else printf("Правый край нижнего ряда.\n");
            }
        } else if (ch == 'A' || ch == 'a' || ch == '4') {
            if (cur->row == 0) {
                // верхний ряд: влево = prev
                if (cur->prev) { cur = cur->prev; PrintNode(cur); }
                else printf("Начало списка (S). Назад нельзя.\n");
            } else {
                // нижний ряд: влево = next
                if (cur->next) { cur = cur->next; PrintNode(cur); }
                else printf("Левый край нижнего ряда.\n");
            }
        } else if (ch == 'S' || ch == 's' || ch == '2') {
            if (cur->row == 0) {
                if (cur->cross) { cur = cur->cross; PrintNode(cur); }
                else printf("Переход вниз невозможен (cross = NULL).\n");
            } else printf("Уже в нижнем ряду.\n");
        } else if (ch == 'W' || ch == 'w' || ch == '8') {
            if (cur->row == 1) {
                if (cur->cross) { cur = cur->cross; PrintNode(cur); }
                else printf("Переход вверх невозможен (cross = NULL).\n");
            } else printf("Уже в верхнем ряду.\n");
        } else if (ch == 'R' || ch == 'r') {
            cur = S; printf("Вернулись к S.\n"); PrintNode(cur);
        } else if (ch == 'Q' || ch == 'q') {
            running = 0;
        } else {
            printf("Неизвестная команда.\n");
        }
    }

    // освобождаем память
    Node *p = S;
    while (p) { Node *nx = p->next; free(p->data); free(p); p = nx; }
    p = botHead;
    while (p) { Node *nx = p->next; free(p->data); free(p); p = nx; }

    return 0;
}
