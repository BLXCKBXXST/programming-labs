#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#define MAX_NAME 64
#define MAX_LEVEL 16
#define MAX_EMPLOYEES 128
#define DATABASE_FILE "database.dat"
#define RLE_FILE      "database.rle"

typedef struct {
    char name[MAX_NAME];
    int  id;
    char level[MAX_LEVEL];
} Employee;

int  load_csv(const char *filename, Employee *employees, int max);
void print_table(const Employee *employees, int count);
int  save_database(const Employee *employees, int count);
void search_by_id(void);
int  compress(void);
int  decompress(void);

#endif
