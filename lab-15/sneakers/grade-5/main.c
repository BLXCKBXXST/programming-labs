#include <stdio.h>
#include <stdlib.h>
#include "employee.h"
#include "menu.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Использование: %s <файл.csv>\n", argv[0]);
        return 1;
    }

    Employee employees[MAX_EMPLOYEES];
    int count = load_csv(argv[1], employees, MAX_EMPLOYEES);
    if (count < 0) return 1;

    printf("Загружено сотрудников: %d\n\n", count);
    print_table(employees, count);

    if (save_database(employees, count) < 0) return 1;
    printf("\nБаза данных сохранена в '%s'\n", DATABASE_FILE);

    run_menu(employees, count);

    return 0;
}
