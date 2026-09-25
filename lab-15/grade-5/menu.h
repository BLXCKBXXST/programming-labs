#ifndef MENU_H
#define MENU_H

#include "record.h"

/* Загрузить файл по расширению и запустить интерактивное меню */
int load_and_run(const char *filename);

/* Интерактивное меню для уже загруженных записей */
void run_menu(Record *records, int count, SourceType src);

#endif
