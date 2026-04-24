#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "record.h"

int load_and_run(const char *filename) {
    const char *ext = strrchr(filename, '.');
    if (!ext) {
        fprintf(stderr, "Ошибка: неизвестный тип файла\n");
        return -1;
    }

    Record records[MAX_RECORDS];
    int count = 0;
    SourceType src;

    if (strcmp(ext, ".csv") == 0) {
        src = SRC_CSV;
        count = load_csv(filename, records, MAX_RECORDS);
    } else if (strcmp(ext, ".dat") == 0) {
        src = SRC_DAT;
        count = load_dat(filename, records, MAX_RECORDS);
    } else if (strcmp(ext, ".rle") == 0) {
        src = SRC_RLE;
        if (decompress() != 0) return -1;
        count = load_dat(RESTORED_FILE, records, MAX_RECORDS);
    } else {
        fprintf(stderr, "Ошибка: неподдерживаемый формат '%s'\n", ext);
        return -1;
    }

    if (count < 0) return -1;

    printf("Загружено записей: %d\n", count);
    run_menu(records, count, src);
    return 0;
}

/*
 * run_menu — интерактивное меню. Пункты формируются динамически
 * в зависимости от типа загруженного файла.
 */
void run_menu(Record *records, int count, SourceType src) {
    int choice;
    do {
        printf("\n=== Меню ===\n");
        printf("1. Поиск записи по ID\n");
        printf("2. Показать все записи\n");
        if (src == SRC_CSV || src == SRC_RLE) printf("3. Сохранить в %s\n", DATABASE_FILE);
        if (src == SRC_DAT || src == SRC_RLE) printf("4. Сохранить в CSV\n");
        if (src == SRC_CSV || src == SRC_DAT) printf("5. Сжать в RLE (%s)\n", RLE_FILE);
        printf("0. Выход\n");
        printf("Выбор: ");
        if (scanf("%d", &choice) != 1) break;
        switch (choice) {
            case 1:
                search_by_id(records, count);
                break;
            case 2:
                print_all(records, count);
                break;
            case 3:
                if (src == SRC_CSV || src == SRC_RLE) {
                    if (save_database(records, count) == 0)
                        printf("Сохранено: '%s'\n", DATABASE_FILE);
                } else printf("Неверный выбор\n");
                break;
            case 4:
                if (src == SRC_DAT || src == SRC_RLE) {
                    char name[128];
                    printf("Имя CSV-файла: ");
                    if (scanf("%127s", name) == 1 && save_csv(records, count, name) == 0)
                        printf("Сохранено: '%s'\n", name);
                } else printf("Неверный выбор\n");
                break;
            case 5:
                if (src == SRC_CSV || src == SRC_DAT) {
                    if (src == SRC_CSV) save_database(records, count);
                    if (compress() == 0) printf("Сжато: '%s'\n", RLE_FILE);
                } else printf("Неверный выбор\n");
                break;
            case 0:
                printf("До свидания!\n");
                break;
            default:
                printf("Неверный выбор\n");
        }
    } while (choice != 0);
}
