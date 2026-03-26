#include <stdio.h>
#include <stdlib.h>  /* malloc, free, rand, srand */
#include <string.h>  /* strcpy */
#include <time.h>    /* time */

/* -------------------------------------------------------
   Структура "комната" (как требует задание)
   ------------------------------------------------------- */
struct room {
    char name[50];   /* имя комнаты          */
    int  level;      /* уровень сложности    */
    int  number;     /* номер комнаты        */
    int  resolution; /* размер комнаты       */
};

/* -------------------------------------------------------
   Узел односвязного списка.
   next — указатель на следующий узел (NULL если конец).
   ------------------------------------------------------- */
struct Node {
    struct room  data; /* данные узла (не указатель, а сама структура) */
    struct Node *next; /* ссылка на следующий узел */
};

/* Создаёт один новый узел со случайными данными */
struct Node *CreateNode(void) {
    /* массивы строк для случайных имён */
    char *names[] = {"Пещера", "Замок", "Лес", "Болото", "Руины"};

    /* выделяем память под узел */
    struct Node *node = malloc(sizeof(struct Node));

    /* заполняем случайными данными */
    strcpy(node->data.name,  names[rand() % 5]);
    node->data.level      = rand() % 10 + 1;  /* от 1 до 10 */
    node->data.number     = rand() % 100 + 1; /* от 1 до 100 */
    node->data.resolution = rand() % 5  + 1;  /* от 1 до 5  */

    node->next = NULL; /* у нового узла нет следующего */
    return node;
}

/* Добавляет новый узел в конец списка */
void PushBack(struct Node **head) {
    struct Node *node = CreateNode();

    /* если список пустой — новый узел становится головой */
    if (*head == NULL) {
        *head = node;
        return;
    }

    /* иначе идём до самого конца и цепляем туда */
    struct Node *cur = *head;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = node;
}

/* Печатает весь список на экран */
void PrintList(struct Node *head) {
    printf("\n%-5s %-15s %-8s %-8s %s\n",
           "№", "Название", "Уровень", "Номер", "Размер");
    printf("----------------------------------------------\n");

    int i = 1; /* счётчик для нумерации строк */
    while (head != NULL) {
        printf("%-5d %-15s %-8d %-8d %d\n",
               i,
               head->data.name,
               head->data.level,
               head->data.number,
               head->data.resolution);
        i++;
        head = head->next; /* переходим к следующему узлу */
    }
}

/* Освобождает всю выделенную память */
void FreeList(struct Node *head) {
    while (head != NULL) {
        struct Node *tmp = head;   /* запоминаем текущий */
        head = head->next;         /* двигаемся вперёд   */
        free(tmp);                 /* удаляем старый     */
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

    struct Node *head = NULL; /* голова списка — пока пустая */

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
