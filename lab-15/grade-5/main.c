#include <stdio.h>
#include "menu.h"

/*
 * main — точка входа. Проверяет аргументы и передаёт управление
 * в load_and_run(), которая определяет тип файла, загружает данные
 * и запускает интерактивное меню.
 */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Использование: %s <файл.csv|файл.dat|файл.rle>\n", argv[0]);
        return 1;
    }
    return load_and_run(argv[1]) == 0 ? 0 : 1;
}
