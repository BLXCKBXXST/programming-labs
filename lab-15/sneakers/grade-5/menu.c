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
        printf("2. Показать всех сотрудников из %s\n", DATABASE_FILE);
        printf("3. Сжать базу данных (RLE)\n");
        printf("4. Восстановить базу из RLE и показать всех\n");
        printf("0. Выход\n");
        printf("Выбор: ");

        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
            case 1:
                search_by_id();
                break;
            case 2:
                print_all_from_dat();
                break;
            case 3:
                compress();
                break;
            case 4:
                if (decompress() == 0) {
                    print_all_from_file(RESTORED_FILE);
                }
                break;
            case 0:
                printf("До свидания!\n");
                break;
            default:
                printf("Неверный выбор\n");
        }
    } while (choice != 0);
}
