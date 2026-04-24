#include <stdio.h>
#include "menu.h"
#include "employee.h"

void run_menu(Employee *employees, int count) {
    (void)employees;
    (void)count;

    int choice;
    do {
        printf("\n=== Меню ===\n");
        printf("1. Поиск сотрудника по ID\n");
        printf("2. Сжать базу данных (RLE)\n");
        printf("3. Восстановить базу данных из RLE\n");
        printf("0. Выход\n");
        printf("Выбор: ");

        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
            case 1:
                search_by_id();
                break;
            case 2:
                compress();
                break;
            case 3:
                decompress();
                break;
            case 0:
                printf("До свидания!\n");
                break;
            default:
                printf("Неверный выбор\n");
        }
    } while (choice != 0);
}
