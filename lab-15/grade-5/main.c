#include <stdio.h>
#include <string.h>
#include "record.h"
#include "menu.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Использование: %s <файл.csv|файл.dat|файл.rle>\n", argv[0]);
        return 1;
    }
    const char *ext = strrchr(argv[1], '.');
    if (!ext) { fprintf(stderr, "Ошибка: неизвестный тип файла\n"); return 1; }

    Record records[MAX_RECORDS];
    int count = 0;
    SourceType src;

    if (strcmp(ext, ".csv") == 0) {
        src = SRC_CSV;
        count = load_csv(argv[1], records, MAX_RECORDS);
    } else if (strcmp(ext, ".dat") == 0) {
        src = SRC_DAT;
        count = load_dat(argv[1], records, MAX_RECORDS);
    } else if (strcmp(ext, ".rle") == 0) {
        src = SRC_RLE;
        if (decompress() != 0) return 1;
        count = load_dat(RESTORED_FILE, records, MAX_RECORDS);
    } else {
        fprintf(stderr, "Ошибка: неподдерживаемый формат '%s'\n", ext);
        return 1;
    }

    if (count < 0) return 1;
    printf("Загружено записей: %d\n", count);
    run_menu(records, count, src);
    return 0;
}
