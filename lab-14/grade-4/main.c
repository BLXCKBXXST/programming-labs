#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* -------------------------------------------------------
   Структура данных — кроссовок
   ------------------------------------------------------- */
typedef struct {
    char brand[20];
    char model[20];
    int  size;
    int  price;
} Sneaker;

/* -------------------------------------------------------
   Узел двусвязного списка.
   data  — указатель на структуру (выделяется отдельно)
   next  — вперёд по списку
   prev  — назад по списку
   ------------------------------------------------------- */
typedef struct Node {
    Sneaker     *data; /* указатель на структуру (пункт 4 задания) */
    struct Node *next;
    struct Node *prev;
} Node;

/* Создаёт структуру Sneaker, заполненную случайными данными */
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

/* Создаёт узел и инициализирует указатель data */
Node *CreateNode(void) {
    Node *node = malloc(sizeof(Node));
    node->data = CreateSneaker(); /* пункт 4: инициализируем указатель на структуру */
    node->next = NULL;
    node->prev = NULL;
    return node;
}

/* Добавляет узел в конец двусвязного списка */
void PushBack(Node **head, Node **tail) {
    Node *node = CreateNode();

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
void PrintNode(Node *node, int idx) {
    printf("[%d] %-10s %-10s размер: %-4d цена: $%d\n",
           idx,
           node->data->brand,
           node->data->model,
           node->data->size,
           node->data->price);
}

/* Освобождает всю память списка */
void FreeList(Node *head) {
    while (head != NULL) {
        Node *tmp = head;
        head = head->next;
        free(tmp->data); /* сначала освобождаем структуру Sneaker */
        free(tmp);       /* потом сам узел                        */
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
    Node *S    = NULL;
    Node *tail = NULL;

    int i = 0;
    for (i = 0; i < n; i++) {
        PushBack(&S, &tail);
    }

    /* навигация по двусвязному списку */
    Node *cur   = S; /* текущая позиция — начало */
    int   idx     = 1;
    int   running = 1;
    char  ch;

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
