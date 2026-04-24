#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "employee.h"

int load_csv(const char *filename, Employee *employees, int max) {
    FILE *f = fopen(filename, "r");
    if (!f) { fprintf(stderr, "Ошибка: не удалось открыть файл '%s'\n", filename); return -1; }
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
        employees[count].name[MAX_NAME - 1] = '\0';
        employees[count].level[MAX_LEVEL - 1] = '\0';
        employees[count].id = atoi(id_s);
        count++;
    }
    fclose(f);
    return count;
}

int load_dat(const char *filename, Employee *employees, int max) {
    FILE *f = fopen(filename, "rb");
    if (!f) { fprintf(stderr, "Ошибка: не удалось открыть файл '%s'\n", filename); return -1; }
    int count = 0;
    if (fread(&count, sizeof(int), 1, f) != 1) { fclose(f); return -1; }
    if (count > max) count = max;
    if (fread(employees, sizeof(Employee), count, f) != (size_t)count) { fclose(f); return -1; }
    fclose(f);
    return count;
}

void print_table(const Employee *employees, int count) {
    printf("%-5s %-24s %-8s %-10s\n", "№", "Имя", "ID", "Уровень");
    printf("%-5s %-24s %-8s %-10s\n", "---", "------------------------", "--------", "----------");
    for (int i = 0; i < count; i++)
        printf("%-5d %-24s %-8d %-10s\n", i+1, employees[i].name, employees[i].id, employees[i].level);
}

int save_database(const Employee *employees, int count) {
    FILE *f = fopen(DATABASE_FILE, "wb");
    if (!f) { fprintf(stderr, "Ошибка: не удалось создать '%s'\n", DATABASE_FILE); return -1; }
    fwrite(&count, sizeof(int), 1, f);
    fwrite(employees, sizeof(Employee), count, f);
    fclose(f);
    return 0;
}

void search_by_id(const Employee *employees, int count) {
    int id;
    printf("Введите ID: ");
    if (scanf("%d", &id) != 1) return;
    for (int i = 0; i < count; i++) {
        if (employees[i].id == id) {
            printf("\nИмя: %s\nID: %d\nУровень: %s\n", employees[i].name, employees[i].id, employees[i].level);
            return;
        }
    }
    fprintf(stderr, "Сотрудник с ID %d не найден\n", id);
}

void print_all(const Employee *employees, int count) {
    printf("\nСотрудников: %d\n\n", count);
    print_table(employees, count);
}
