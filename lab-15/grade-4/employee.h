#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#define MAX_NAME 64
#define MAX_LEVEL 16
#define MAX_EMPLOYEES 128
#define DATABASE_FILE "database.dat"

typedef struct {
    char name[MAX_NAME];
    int  id;
    char level[MAX_LEVEL];
} Employee;

typedef enum {
    SRC_CSV,
    SRC_DAT
} SourceType;

int  load_csv(const char *filename, Employee *employees, int max);
int  load_dat(const char *filename, Employee *employees, int max);
void print_table(const Employee *employees, int count);
void print_all(const Employee *employees, int count);
int  save_database(const Employee *employees, int count);
int  save_csv(const Employee *employees, int count, const char *filename);
void search_by_id(const Employee *employees, int count);

#endif
