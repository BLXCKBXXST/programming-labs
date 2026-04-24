#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/list.h"

// главная функция — строит двухрядную структуру и запускает навигацию
int main(int argc, char *argv[]) {
    int N = 0, K = 0;

    // N — длина верхнего ряда, K — длина нижнего
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

    // --- строим верхний ряд (next → вправо) ---
    Node *S       = NULL; // S — начало, как требует задание
    Node *topTail = NULL;
    int i = 0;
    for (i = 0; i < N; i++) {
        Node *node = CreateNode(0);
        if (S == NULL) {
            S = node;
            topTail = node;
        } else {
            topTail->next = node;
            topTail = node;
        }
    }

    // --- строим нижний ряд (next → влево, т.е. добавляем в начало) ---
    Node *botHead = NULL; // левый край нижнего ряда
    Node *botTail = NULL; // правый край — под верхним [N-1]
    for (i = 0; i < K; i++) {
        Node *node = CreateNode(1);
        // добавляем в начало, чтобы обход next шёл влево
        node->next = botHead;
        botHead = node;
        if (botTail == NULL) {
            botTail = node; // первый добавленный = правый край
        }
    }

    // сохраняем нижний ряд в массив (слева направо).
    // botHead — левый край, next идёт влево (к botTail, у которого next=NULL).
    // Поэтому итерируемся от botHead и заполняем bot[0..K-1] слева направо.
    Node **bot = malloc(K * sizeof(Node *));
    Node *cur  = botHead;
    for (i = 0; i < K; i++) {
        bot[i] = cur;
        cur    = cur->next;
    }

    // расставляем cross: где ряды перекрываются — двусторонняя связь,
    // где длинный выходит за короткий — cross = NULL (пункт 7)
    int minLen = (N < K) ? N : K;
    Node *t = S;
    for (i = 0; i < minLen; i++) {
        t->cross      = bot[i]; // верхний → нижний
        bot[i]->cross = t;      // нижний → верхний
        t = t->next;
    }
    free(bot); // вспомогательный массив, освобождаем

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
                if (cur->next != NULL) { cur = cur->next; PrintNode(cur); }
                else printf("Конец верхнего ряда.\n");
            } else {
                // нижний ряд: вправо = вверх → next → вниз
                if (cur->cross != NULL && cur->cross->next != NULL
                    && cur->cross->next->cross != NULL) {
                    cur = cur->cross->next->cross;
                    PrintNode(cur);
                } else printf("Конец нижнего ряда.\n");
            }
        } else if (ch == 'A' || ch == 'a' || ch == '4') {
            if (cur->row == 0) {
                if (cur == S) { printf("Начало списка (S). Назад нельзя.\n"); }
                else {
                    Node *p = S;
                    while (p->next != NULL && p->next != cur) p = p->next;
                    cur = p; PrintNode(cur);
                }
            } else {
                if (cur->next != NULL) { cur = cur->next; PrintNode(cur); }
                else printf("Левый край нижнего ряда.\n");
            }
        } else if (ch == 'S' || ch == 's' || ch == '2') {
            if (cur->row == 0) {
                if (cur->cross != NULL) { cur = cur->cross; PrintNode(cur); }
                else printf("Переход вниз невозможен (cross = NULL).\n");
            } else printf("Уже в нижнем ряду.\n");
        } else if (ch == 'W' || ch == 'w' || ch == '8') {
            if (cur->row == 1) {
                if (cur->cross != NULL) { cur = cur->cross; PrintNode(cur); }
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

    // освобождаем память обоих рядов
    Node *p = S;
    while (p != NULL) { Node *nx = p->next; free(p->data); free(p); p = nx; }
    p = botHead;
    while (p != NULL) { Node *nx = p->next; free(p->data); free(p); p = nx; }

    return 0;
}
