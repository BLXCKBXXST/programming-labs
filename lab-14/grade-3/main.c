#include <stdio.h>
#include <stdlib.h>  /* malloc, free, rand, srand */
#include <string.h>  /* strcpy */
#include <time.h>    /* time */

/* -------------------------------------------------------
   Структура данных — кроссовок
   ------------------------------------------------------- */
typedef struct {
    char brand[20];  /* бренд   */
    char model[20];  /* модель  */
    int  size;       /* размер  */
    int  price;      /* цена    */
} Sneaker;

/* -------------------------------------------------------
   Узел односвязного списка.
   next — указатель на следующий узел (NULL если конец).
   ------------------------------------------------------- */
typedef struct Node {
    Sneaker      data; /* данные узла (сама структура, не указатель) */
    struct Node *next; /* ссылка на следующий узел */
} Node;

/* Создаёт один новый узел со случайными данными */
Node *CreateNode(void) {
    char *brands[] = {"Nike", "Adidas", "Puma"};
    char *models[] = {"Pro", "Super", "Ultra"};
    int   prices[] = {200, 250, 300, 350, 400, 450, 500};

    /* выделяем память под узел */
    Node *node = malloc(sizeof(Node));

    /* заполняем случайными данными */
    strcpy(node->data.brand, brands[rand() % 3]);
    strcpy(node->data.model, models[rand() % 3]);
    node->data.size  = 36 + rand() % 9;  /* от 36 до 44 */
    node->data.price = prices[rand() % 7];

    node->next = NULL; /* у нового узла нет следующего */
    return node;
}

/* Добавляет новый узел в конец списка */
void PushBack(Node **head) {
    Node *node = CreateNode();

    /* если список пустой — новый узел становится головой */
    if (*head == NULL) {
        *head = node;
        return;
    }

    /* иначе идём до самого конца и цепляем туда */
    Node *cur = *head;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = node;
}

/* Печатает весь список на экран */
void PrintList(Node *head) {
    printf("\n%-5s %-10s %-10s %-8s %s\n",
           "№", "Бренд", "Модель", "Размер", "Цена");
    printf("─────────────────────────────────────────────\n");

    int i = 1; /* счётчик для нумерации строк */
    while (head != NULL) {
        printf("%-5d %-10s %-10s %-8d $%d\n",
               i,
               head->data.brand,
               head->data.model,
               head->data.size,
               head->data.price);
        i++;
        head = head->next; /* переходим к следующему узлу */
    }
}

/* Освобождает всю выделенную память */
void FreeList(Node *head) {
    while (head != NULL) {
        Node *tmp = head;   /* запоминаем текущий */
        head = head->next;  /* двигаемся вперёд   */
        free(tmp);          /* удаляем старый     */
    }
}

int main(int argc, char *argv[]) {
    int n = 0;

    /* n можно передать аргументом или ввести с клавиатуры */
    if (argc > 1) {
        n = atoi(argv[1]); /* atoi — строку превращает в число */
    } else {
        printf("Введите количество элементов: ");
        scanf("%d", &n);
    }

    /* инициализируем генератор случайных чисел */
    srand(time(NULL));

    Node *head = NULL; /* голова списка — пока пустая */

    /* добавляем n узлов */
    int i = 0; /* объявляем отдельно — стиль C89 */
    for (i = 0; i < n; i++) {
        PushBack(&head); /* передаём адрес указателя, чтобы можно было изменить */
    }

    printf("Односвязный список (%d элементов):", n);
    PrintList(head);

    FreeList(head); /* всегда освобождаем память в конце */
    return 0;
}
