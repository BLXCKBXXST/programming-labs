#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME      64
#define MAX_LEVEL     16
#define MAX_EMPLOYEES 128
#define BUF_SIZE      256

typedef struct {
    char name[MAX_NAME];
    int  id;
    char level[MAX_LEVEL];
} Employee;

/* Вывод строки в файловый дескриптор */
static void fd_puts(int fd, const char *s) {
    write(fd, s, strlen(s));
}

/* Аналог fgets() на базе read(): читает побайтово до '\n' или EOF */
static int fd_gets(int fd, char *buf, int max) {
    int i = 0;
    char c;
    while (i < max - 1) {
        ssize_t n = read(fd, &c, 1);
        if (n <= 0) break;          /* EOF или ошибка */
        buf[i++] = c;
        if (c == '\n') break;
    }
    buf[i] = '\0';
    return i;                       /* 0 = EOF */
}

/* Форматирование целого числа в строку, возвращает длину */
static int int_to_str(int n, char *out) {
    char tmp[32];
    int len = 0;
    if (n < 0) { out[len++] = '-'; n = -n; }
    int start = len;
    do { tmp[len++ - start] = '0' + n % 10; n /= 10; } while (n);
    int digits = len - start;
    for (int i = 0; i < digits; i++) out[start + i] = tmp[digits - 1 - i];
    out[len] = '\0';
    return len;
}

/* Вывод строки фиксированной ширины, дополненной пробелами */
static void print_col(int fd, const char *s, int width) {
    int len = (int)strlen(s);
    write(fd, s, len > width ? width : len);
    for (int i = len; i < width; i++) write(fd, " ", 1);
    write(fd, " ", 1);
}

static int load_csv(const char *filename, Employee *employees, int max) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        fd_puts(STDERR_FILENO, "Ошибка: не удалось открыть файл '\0'");
        fd_puts(STDERR_FILENO, filename);
        fd_puts(STDERR_FILENO, "'\n");
        return -1;
    }

    int count = 0;
    char line[BUF_SIZE];

    while (count < max && fd_gets(fd, line, sizeof(line)) > 0) {
        /* Убираем '\r' и '\n' */
        int len = (int)strlen(line);
        while (len > 0 && (line[len-1] == '\n' || line[len-1] == '\r'))
            line[--len] = '\0';
        if (len == 0) continue;

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

    close(fd);
    return count;
}

static void print_table(const Employee *employees, int count) {
    int out = STDOUT_FILENO;
    print_col(out, "№",   5);
    print_col(out, "Имя", 24);
    print_col(out, "ID",  8);
    fd_puts(out, "Уровень\n");
    print_col(out, "---",  5);
    print_col(out, "------------------------", 24);
    print_col(out, "--------", 8);
    fd_puts(out, "----------\n");

    for (int i = 0; i < count; i++) {
        char num[16], id_s[16];
        int_to_str(i + 1, num);
        int_to_str(employees[i].id, id_s);
        print_col(out, num,                5);
        print_col(out, employees[i].name,  24);
        print_col(out, id_s,               8);
        fd_puts(out, employees[i].level);
        fd_puts(out, "\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fd_puts(STDERR_FILENO, "Использование: ");
        fd_puts(STDERR_FILENO, argv[0]);
        fd_puts(STDERR_FILENO, " <файл.csv>\n");
        return 1;
    }

    Employee employees[MAX_EMPLOYEES];
    int count = load_csv(argv[1], employees, MAX_EMPLOYEES);
    if (count < 0) return 1;

    char num[16];
    int_to_str(count, num);
    fd_puts(STDOUT_FILENO, "Загружено сотрудников: ");
    fd_puts(STDOUT_FILENO, num);
    fd_puts(STDOUT_FILENO, "\n\n");
    print_table(employees, count);

    return 0;
}
