#include <stdio.h>
#include "menu.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Использование: %s <файл.csv|файл.dat|файл.rle>\n", argv[0]);
        return 1;
    }
    return load_and_run(argv[1]) == 0 ? 0 : 1;
}
