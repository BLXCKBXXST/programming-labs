#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/list.h"

// главная функция — только вызываем готовые функции из list.c
int main(int argc, char *argv[]) {
    int n = 0;

    if (argc > 1) {
        n = atoi(argv[1]);
    } else {
        printf("Введите количество элементов: ");
        scanf("%d", &n);
    }

    srand(time(NULL));

    // S — указатель на начало списка (как требует задание)
    Node *S    = NULL;
    Node *tail = NULL;

    int i = 0;
    for (i = 0; i < n; i++) {
        PushBack(&S, &tail);
    }

    // навигация по двусвязному списку
    Node *cur     = S;
    int   idx     = 1;
    int   running = 1;
    char  ch;

    printf("\nНавигация: D/6 — вперёд, A/4 — назад, Q — выход\n");
    printf("Начинаем с S (начало списка):\n");
    PrintNode(cur, idx);

    while (running) {
        printf("Ввод: ");
        scanf(" %c", &ch); // пробел перед %c — чтобы не захватить '\n'

        if (ch == 'D' || ch == 'd' || ch == '6') {
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
