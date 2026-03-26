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

/* -------------------------------------------------------
   Узел двусвязного списка.
   data  — указатель на структуру (выделяется отдельно)
   next  — вперёд по списку
   prev  — назад по списку
   ------------------------------------------------------- */
struct Node {
    struct room *data; /* указатель на структуру (пункт 4 задания) */
    struct Node *next;
    struct Node *prev;
};

/* Создаёт структуру room, заполненную случайными данными */
struct room *CreateRoom(void) {
    char *names[] = {"Пещера", "Замок", "Лес", "Болото", "Руины"};
    struct room *r = malloc(sizeof(struct room));
    strcpy(r->name,  names[rand() % 5]);
    r->level      = rand() % 10 + 1;
    r->number     = rand() % 100 + 1;
    r->resolution = rand() % 5  + 1;
    return r;
}

/* Создаёт узел и инициализирует указатель data */
struct Node *CreateNode(void) {
    struct Node *node = malloc(sizeof(struct Node));
    node->data = CreateRoom(); /* пункт 4: инициализируем указатель на структуру */
    node->next = NULL;
    node->prev = NULL;
    return node;
}

/* Добавляет узел в конец двусвязного списка */
void PushBack(struct Node **head, struct Node **tail) {
    struct Node *node = CreateNode();

    if (*head == NULL) {
        /* список пустой — узел и голова и хвост */
        *head = node;
        *tail = node;
        return;
    }

    /* связываем новый узел с хвостом */
    node->prev    = *tail;  /* новый узел смотрит назад на старый хвост */
    (*tail)->next = node;   /* старый хвост смотрит вперёд на новый     */
    *tail = node;           /* обновляем хвост                          */
}

/* Печатает информацию об одном узле */
void PrintNode(struct Node *node, int idx) {
    printf("[%d] %-15s уровень: %-3d номер: %-4d размер: %d\n",
           idx,
           node->data->name,
           node->data->level,
           node->data->number,
           node->data->resolution);
}

/* Освобождает всю память списка */
void FreeList(struct Node *head) {
    while (head != NULL) {
        struct Node *tmp = head;
        head = head->next;
        free(tmp->data); /* сначала освобождаем структуру room */
        free(tmp);       /* потом сам узел                     */
    }
}

int main(int argc, char *argv[]) {
    int n = 0;

    if (argc > 1) {
        n = atoi(argv[1]);
    } else {
        printf("Введите количество элементов: ");
        scanf("%d", &n);
    }

    srand(time(NULL));

    /* S — указатель на начало списка (как требует задание) */
    struct Node *S    = NULL;
    struct Node *tail = NULL;

    int i = 0;
    for (i = 0; i < n; i++) {
        PushBack(&S, &tail);
    }

    /* навигация по двусвязному списку */
    struct Node *cur = S; /* текущая позиция — начало */
    int idx = 1;
    int running = 1;
    char ch;

    printf("\nНавигация: D/6 — вперёд, A/4 — назад, Q — выход\n");
    printf("Начинаем с S (начало списка):\n");
    PrintNode(cur, idx);

    while (running) {
        printf("Ввод: ");
        scanf(" %c", &ch); /* пробел перед %c — чтобы не захватить '\n' */

        if (ch == 'D' || ch == 'd' || ch == '6') {
            /* движение вправо */
            if (cur->next != NULL) {
                cur = cur->next;
                idx++;
                PrintNode(cur, idx);
            } else {
                printf("Достигли конца списка. Вернуться к S? (y/n): ");
                scanf(" %c", &ch);
                if (ch == 'y' || ch == 'Y') {
                    cur = S;
                    idx = 1;
                    printf("Вернулись к S.\n");
                    PrintNode(cur, idx);
                }
            }
        } else if (ch == 'A' || ch == 'a' || ch == '4') {
            /* движение влево */
            if (cur->prev != NULL) {
                cur = cur->prev;
                idx--;
                PrintNode(cur, idx);
            } else {
                printf("Начало списка (позиция S). Двигаться назад нельзя.\n");
            }
        } else if (ch == 'Q' || ch == 'q') {
            running = 0;
        } else {
            printf("Неизвестная команда. Используйте D, A или Q.\n");
        }
    }

    FreeList(S);
    return 0;
}
