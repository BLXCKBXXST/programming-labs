#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* -------------------------------------------------------
   Структура данных — комната
   ------------------------------------------------------- */
struct room {
    char name[50];
    int  level;
    int  number;
    int  resolution;
};

/*
 * Схема структуры (Вариант 1):
 *
 *  S → [1] → [2] → [3] → ... → [N] → NULL   (верхний ряд, слева направо)
 *       |      |     |              |
 *      [1] ← [2] ← [3] ← ... ← [K] → NULL  (нижний ряд, справа налево)
 *
 * cross — вертикальная связь между рядами.
 * Если списки разной длины — cross у "лишних" узлов = NULL.
 */

struct Node {
    struct room *data;  /* указатель на данные                  */
    struct Node *next;  /* следующий в своём ряду               */
    struct Node *cross; /* вертикальная связь (верх ↔ низ)      */
    int          row;   /* 0 = верхний ряд, 1 = нижний ряд      */
};

/* Создаёт структуру room со случайными данными */
struct room *CreateRoom(void) {
    char *names[] = {"Пещера", "Замок", "Лес", "Болото", "Руины"};
    struct room *r = malloc(sizeof(struct room));
    strcpy(r->name,  names[rand() % 5]);
    r->level      = rand() % 10 + 1;
    r->number     = rand() % 100 + 1;
    r->resolution = rand() % 5  + 1;
    return r;
}

/* Создаёт узел для указанного ряда (0 или 1) */
struct Node *CreateNode(int row) {
    struct Node *node = malloc(sizeof(struct Node));
    node->data  = CreateRoom();
    node->next  = NULL;
    node->cross = NULL; /* сначала без вертикальных связей */
    node->row   = row;
    return node;
}

/* Печатает один узел с указанием ряда */
void PrintNode(struct Node *node) {
    printf("[%s] %-15s уровень: %-3d номер: %-4d размер: %d\n",
           node->row == 0 ? "верх" : "низ ",
           node->data->name,
           node->data->level,
           node->data->number,
           node->data->resolution);
}

int main(int argc, char *argv[]) {
    int N = 0, K = 0;

    /* N — длина верхнего ряда, K — длина нижнего */
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

    /* --- строим верхний ряд (next → вправо) --- */
    struct Node *S       = NULL; /* S — начало, как требует задание */
    struct Node *topTail = NULL;
    int i = 0;
    for (i = 0; i < N; i++) {
        struct Node *node = CreateNode(0);
        if (S == NULL) {
            S = node;
            topTail = node;
        } else {
            topTail->next = node;
            topTail = node;
        }
    }

    /* --- строим нижний ряд (next → влево, т.е. добавляем в начало) --- */
    struct Node *botHead = NULL; /* левый край нижнего ряда */
    struct Node *botTail = NULL; /* правый край — под верхним [1] */
    for (i = 0; i < K; i++) {
        struct Node *node = CreateNode(1);
        /* добавляем в начало, чтобы обход next шёл влево */
        node->next = botHead;
        botHead = node;
        if (botTail == NULL) {
            botTail = node; /* первый добавленный = правый край */
        }
    }

    /*
     * Сохраняем нижний ряд в массив (слева направо),
     * чтобы удобно расставить вертикальные связи cross.
     */
    struct Node **bot = malloc(K * sizeof(struct Node *));
    struct Node *cur  = botTail;
    for (i = K - 1; i >= 0; i--) {
        bot[i] = cur;
        cur    = cur->next;
    }

    /*
     * Расставляем cross между верхним и нижним рядами.
     * Где ряды перекрываются — двусторонняя связь.
     * Где длинный выходит за короткий — cross = NULL (пункт 7).
     */
    int minLen = (N < K) ? N : K; /* минимум из двух длин */
    struct Node *t = S;
    for (i = 0; i < minLen; i++) {
        t->cross      = bot[i]; /* верхний → нижний */
        bot[i]->cross = t;      /* нижний → верхний */
        t = t->next;
    }
    /* у "лишних" узлов верхнего ряда cross уже NULL (из CreateNode) */
    /* у "лишних" узлов нижнего ряда тоже */
    free(bot); /* массив вспомогательный, освобождаем */

    /* --- навигация --- */
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
            /* вправо — зависит от ряда */
            if (cur->row == 0) {
                /* верхний ряд: вправо = next */
                if (cur->next != NULL) {
                    cur = cur->next;
                    PrintNode(cur);
                } else {
                    printf("Конец верхнего ряда.\n");
                }
            } else {
                /*
                 * Нижний ряд: next указывает влево!
                 * Чтобы идти вправо, нужно подняться через cross,
                 * шагнуть вперёд по верхнему, и снова опуститься.
                 */
                if (cur->cross != NULL && cur->cross->next != NULL
                    && cur->cross->next->cross != NULL) {
                    cur = cur->cross->next->cross;
                    PrintNode(cur);
                } else {
                    printf("Конец нижнего ряда.\n");
                }
            }
        } else if (ch == 'A' || ch == 'a' || ch == '4') {
            /* влево */
            if (cur->row == 0) {
                /* верхний ряд: ищем предыдущий (нет prev, обходим с головы) */
                if (cur == S) {
                    printf("Начало списка (S). Назад нельзя.\n");
                } else {
                    struct Node *p = S;
                    while (p->next != NULL && p->next != cur) {
                        p = p->next;
                    }
                    cur = p;
                    PrintNode(cur);
                }
            } else {
                /* нижний ряд: next — это влево */
                if (cur->next != NULL) {
                    cur = cur->next;
                    PrintNode(cur);
                } else {
                    printf("Левый край нижнего ряда.\n");
                }
            }
        } else if (ch == 'S' || ch == 's' || ch == '2') {
            /* вниз (cross) */
            if (cur->row == 0) {
                if (cur->cross != NULL) {
                    cur = cur->cross;
                    PrintNode(cur);
                } else {
                    printf("Переход вниз невозможен (cross = NULL).\n");
                }
            } else {
                printf("Уже в нижнем ряду.\n");
            }
        } else if (ch == 'W' || ch == 'w' || ch == '8') {
            /* вверх (cross) */
            if (cur->row == 1) {
                if (cur->cross != NULL) {
                    cur = cur->cross;
                    PrintNode(cur);
                } else {
                    printf("Переход вверх невозможен (cross = NULL).\n");
                }
            } else {
                printf("Уже в верхнем ряду.\n");
            }
        } else if (ch == 'R' || ch == 'r') {
            cur = S;
            printf("Вернулись к S.\n");
            PrintNode(cur);
        } else if (ch == 'Q' || ch == 'q') {
            running = 0;
        } else {
            printf("Неизвестная команда.\n");
        }
    }

    /* освобождаем память обоих рядов */
    struct Node *p = S;
    while (p != NULL) {
        struct Node *nx = p->next;
        free(p->data);
        free(p);
        p = nx;
    }
    p = botHead;
    while (p != NULL) {
        struct Node *nx = p->next;
        free(p->data);
        free(p);
        p = nx;
    }

    return 0;
}
