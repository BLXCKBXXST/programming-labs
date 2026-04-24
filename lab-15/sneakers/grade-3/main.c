#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 64
#define MAX_LEVEL 16
#define MAX_EMPLOYEES 128

typedef struct {
    char name[MAX_NAME];
    int  id;
    char level[MAX_LEVEL];
} Employee;

int load_csv(const char *filename, Employee *employees, int max) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        fprintf(stderr, "Ошибка: не удалось открыть файл '%s'\n", filename);
        return -1;
    }

    int count = 0;
    char line[256];

    while (count < max && fgets(line, sizeof(line), f)) {
        line[strcspn(line, "\r\n")] = '\0';
        if (line[0] == '\0') continue;

        char *name  = strtok(line, ";");
        char *id_s  = strtok(NULL, ";");
        char *level = strtok(NULL, ";");

        if (!name || !id_s || !level) continue;

        strncpy(employees[count].name,  name,  MAX_NAME  - 1);
        strncpy(employees[count].level, level, MAX_LEVEL - 1);
        employees[count].name[MAX_NAME   - 1] = '\0';
        employees[count].level[MAX_LEVEL - 1] = '\0';
        employees[count].id = atoi(id_s);
        count++;
    }

    fclose(f);
    return count;
}

void print_table(const Employee *employees, int count) {
    printf("%-5s %-24s %-8s %-10s\n", "№", "Имя", "ID", "Уровень");
    printf("%-5s %-24s %-8s %-10s\n", "---", "------------------------", "--------", "----------");
    for (int i = 0; i < count; i++) {
        printf("%-5d %-24s %-8d %-10s\n",
               i + 1,
               employees[i].name,
               employees[i].id,
               employees[i].level);
    }
}

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

    return 0;
}
