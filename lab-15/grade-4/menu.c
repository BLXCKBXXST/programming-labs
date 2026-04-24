#include <stdio.h>
#include "menu.h"
#include "employee.h"

void run_menu(Employee *employees, int count, SourceType src) {
    int choice;
    do {
        printf("\n=== Меню ===\n");
        printf("1. Поиск сотрудника по ID\n");
        printf("2. Показать всех сотрудников\n");
        if (src == SRC_CSV)
            printf("3. Сохранить в %s\n", DATABASE_FILE);
        printf("0. Выход\n");
        printf("Выбор: ");
        if (scanf("%d", &choice) != 1) break;
        switch (choice) {
            case 1: search_by_id(employees, count); break;
            case 2: print_all(employees, count); break;
            case 3:
                if (src == SRC_CSV && save_database(employees, count) == 0)
                    printf("Сохранено: '%s'\n", DATABASE_FILE);
                else if (src != SRC_CSV)
                    printf("Неверный выбор\n");
                break;
            case 0: printf("До свидания!\n"); break;
            default: printf("Неверный выбор\n");
        }
    } while (choice != 0);
}
