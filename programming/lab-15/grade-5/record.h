#ifndef RECORD_H
#define RECORD_H

#define MAX_NAME 64
#define MAX_LEVEL 16
#define MAX_RECORDS 128
#define DATABASE_FILE  "database.dat"
#define RLE_FILE       "database.rle"
#define RESTORED_FILE  "database_restored.dat"

typedef struct {
    char name[MAX_NAME];
    int  id;
    char level[MAX_LEVEL];
} Record;

typedef enum { SRC_CSV, SRC_DAT, SRC_RLE } SourceType;

int  load_csv(const char *filename, Record *records, int max);
int  load_dat(const char *filename, Record *records, int max);
void print_table(const Record *records, int count);
void print_all(const Record *records, int count);
int  save_database(const Record *records, int count);
int  save_csv(const Record *records, int count, const char *filename);
void search_by_id(const Record *records, int count);
int  compress(void);
int  decompress(void);

#endif
