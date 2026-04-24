#include <stdio.h>
#include "menu.h"
#include "employee.h"

void run_menu(Employee *employees, int count, SourceType src) {
    int choice;
    do {
        printf("\n=== Меню ===\n");
        printf("1. Поиск сотрудника по ID\n");
        printf("2. Показать всех сотрудников\n");
        if (src == SRC_CSV) printf("3. Сохранить в database.dat\n");
        if (src == SRC_DAT) printf("4. Сохранить в CSV\n");
        printf("0. Выход\n");
        printf("Выбор: ");
        if (scanf("%d", &choice) != 1) break;
        switch (choice) {
            case 1: search_by_id(employees, count); break;
            case 2: print_all(employees, count); break;
            case 3:
                if (src == SRC_CSV) {
                    if (save_database(employees, count) == 0)
                        printf("Сохранено: '%s'\n", DATABASE_FILE);
                } else printf("Неверный выбор\n");
                break;
            case 4:
                if (src == SRC_DAT) {
                    char name[128];
                    printf("Имя CSV-файла: ");
                    if (scanf("%127s", name) == 1 && save_csv(employees, count, name) == 0)
                        printf("Сохранено: '%s'\n", name);
                } else printf("Неверный выбор\n");
                break;
            case 0: printf("До свидания!\n"); break;
            default: printf("Неверный выбор\n");
        }
    } while (choice != 0);
}
