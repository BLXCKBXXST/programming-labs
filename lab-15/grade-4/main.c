#include <stdio.h>
#include <string.h>
#include "employee.h"
#include "menu.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Использование: %s <файл.csv|файл.dat>\n", argv[0]);
        return 1;
    }
    const char *ext = strrchr(argv[1], '.');
    if (!ext) { fprintf(stderr, "Ошибка: неизвестный тип файла\n"); return 1; }

    Employee employees[MAX_EMPLOYEES];
    int count = 0;
    SourceType src;

    if      (strcmp(ext, ".csv") == 0) { src = SRC_CSV; count = load_csv(argv[1], employees, MAX_EMPLOYEES); }
    else if (strcmp(ext, ".dat") == 0) { src = SRC_DAT; count = load_dat(argv[1], employees, MAX_EMPLOYEES); }
    else { fprintf(stderr, "Ошибка: неподдерживаемый формат '%s'\n", ext); return 1; }

    if (count < 0) return 1;
    printf("Загружено: %d сотрудников\n", count);
    run_menu(employees, count, src);
    return 0;
}
