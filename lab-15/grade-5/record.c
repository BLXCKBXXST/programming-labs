#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "record.h"

int load_csv(const char *filename, Record *records, int max) {
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
        strncpy(records[count].name,  name,  MAX_NAME  - 1);
        strncpy(records[count].level, level, MAX_LEVEL - 1);
        records[count].name[MAX_NAME - 1] = '\0';
        records[count].level[MAX_LEVEL - 1] = '\0';
        records[count].id = atoi(id_s);
        count++;
    }
    fclose(f);
    return count;
}

int load_dat(const char *filename, Record *records, int max) {
    FILE *f = fopen(filename, "rb");
    if (!f) { fprintf(stderr, "Ошибка: не удалось открыть файл '%s'\n", filename); return -1; }
    int count = 0;
    if (fread(&count, sizeof(int), 1, f) != 1) { fclose(f); return -1; }
    if (count > max) count = max;
    if (fread(records, sizeof(Record), count, f) != (size_t)count) { fclose(f); return -1; }
    fclose(f);
    return count;
}

void print_table(const Record *records, int count) {
    int w = 16;
    for (int i = 0; i < count; i++) {
        int l = (int)strlen(records[i].name);
        if (l > w) w = l;
    }
    printf("%-5s %-*s %-8s %-12s\n", "No", w, "Название", "ID", "Категория");
    printf("%-5s %-*s %-8s %-12s\n", "---", w, "----------------", "--------", "------------");
    for (int i = 0; i < count; i++)
        printf("%-5d %-*s %-8d %-12s\n", i+1, w, records[i].name, records[i].id, records[i].level);
}

void print_all(const Record *records, int count) {
    printf("\nЗаписей: %d\n\n", count);
    print_table(records, count);
}

int save_database(const Record *records, int count) {
    FILE *f = fopen(DATABASE_FILE, "wb");
    if (!f) { fprintf(stderr, "Ошибка: не удалось создать '%s'\n", DATABASE_FILE); return -1; }
    fwrite(&count, sizeof(int), 1, f);
    fwrite(records, sizeof(Record), count, f);
    fclose(f);
    return 0;
}

int save_csv(const Record *records, int count, const char *filename) {
    FILE *f = fopen(filename, "w");
    if (!f) { fprintf(stderr, "Ошибка: не удалось создать '%s'\n", filename); return -1; }
    for (int i = 0; i < count; i++)
        fprintf(f, "%s;%d;%s\n", records[i].name, records[i].id, records[i].level);
    fclose(f);
    return 0;
}

void search_by_id(const Record *records, int count) {
    int id;
    printf("Введите ID: ");
    if (scanf("%d", &id) != 1) return;
    for (int i = 0; i < count; i++) {
        if (records[i].id == id) {
            printf("\nНазвание: %s\nID: %d\nКатегория: %s\n",
                   records[i].name, records[i].id, records[i].level);
            return;
        }
    }
    fprintf(stderr, "Запись с ID %d не найдена\n", id);
}

int compress(void) {
    FILE *in = fopen(DATABASE_FILE, "rb");
    if (!in) { fprintf(stderr, "Ошибка: не удалось открыть '%s'\n", DATABASE_FILE); return -1; }
    FILE *out = fopen(RLE_FILE, "wb");
    if (!out) { fprintf(stderr, "Ошибка: не удалось создать '%s'\n", RLE_FILE); fclose(in); return -1; }
    int cur = fgetc(in);
    while (cur != EOF) {
        unsigned char val = (unsigned char)cur;
        unsigned char cnt = 1;
        int next;
        while (cnt < 255 && (next = fgetc(in)) != EOF && (unsigned char)next == val) cnt++;
        fputc(cnt, out); fputc(val, out);
        cur = (cnt < 255) ? ((next == EOF) ? EOF : next) : fgetc(in);
    }
    fclose(in); fclose(out);
    FILE *f1 = fopen(DATABASE_FILE, "rb"), *f2 = fopen(RLE_FILE, "rb");
    if (f1 && f2) {
        fseek(f1, 0, SEEK_END); long s1 = ftell(f1);
        fseek(f2, 0, SEEK_END); long s2 = ftell(f2);
        fclose(f1); fclose(f2);
        printf("До: %.2f Кб -> После: %.2f Кб. Сжатие: %.1f%%\n",
               s1/1024.0, s2/1024.0, s1 > 0 ? (1.0-(double)s2/s1)*100.0 : 0.0);
    }
    return 0;
}

int decompress(void) {
    FILE *in = fopen(RLE_FILE, "rb");
    if (!in) { fprintf(stderr, "Ошибка: не удалось открыть '%s'\n", RLE_FILE); return -1; }
    FILE *out = fopen(RESTORED_FILE, "wb");
    if (!out) { fprintf(stderr, "Ошибка: не удалось создать '%s'\n", RESTORED_FILE); fclose(in); return -1; }
    int c;
    while ((c = fgetc(in)) != EOF) {
        unsigned char cnt = (unsigned char)c;
        int val = fgetc(in);
        if (val == EOF) { fprintf(stderr, "Повреждённый RLE-файл\n"); fclose(in); fclose(out); return -1; }
        for (unsigned char i = 0; i < cnt; i++) fputc(val, out);
    }
    fclose(in); fclose(out);
    return 0;
}
