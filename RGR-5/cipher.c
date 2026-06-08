#include "cipher.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>

/* =========================================================
 * Таблица латиница 5x5 (ключ = стандартный алфавит, I/J объединены)
 * ========================================================= */
const char lat_table[LAT_SIZE][LAT_SIZE] = {
    {'A','B','C','D','E'},
    {'F','G','H','I','K'},
    {'L','M','N','O','P'},
    {'Q','R','S','T','U'},
    {'V','W','X','Y','Z'}
};

/* =========================================================
 * Таблица кириллица 6x6 (русский алфавит без Ё и Ъ = 30 букв,
 * заполняем 36 ячеек: добавляем пробел и повтор Ю,Я)
 * Хранится как однобайтовые индексы (0..35), отображение в UTF-8
 * выполняется через массив cyr_chars.
 * ========================================================= */

/* Русские буквы в кодировке UTF-8 (без Ё, без Ъ) + пробел */
static const char *cyr_chars[CYR_SIZE * CYR_SIZE] = {
    "А","Б","В","Г","Д","Е",
    "Ж","З","И","Й","К","Л",
    "М","Н","О","П","Р","С",
    "Т","У","Ф","Х","Ц","Ч",
    "Ш","Щ","Ы","Ь","Э","Ю",
    "Я"," "," "," "," "," "
};
/* Количество реально используемых кирилличных «букв» (31 = 30 букв + пробел) */
#define CYR_CHARS_USED 31

/* =========================================================
 * Вспомогательные функции поиска
 * ========================================================= */

/* Ищет латинскую букву в таблице, возвращает 1 если найдена */
static int find_lat(char ch, int *row, int *col)
{
    int r, c;
    char up = (char)toupper((unsigned char)ch);
    if (up == 'J') up = 'I'; /* I и J объединены */
    for (r = 0; r < LAT_SIZE; r++)
        for (c = 0; c < LAT_SIZE; c++)
            if (lat_table[r][c] == up) {
                *row = r; *col = c;
                return 1;
            }
    return 0;
}

/*
 * Ищет кирилличный символ (UTF-8, 2 байта) в таблице.
 * src указывает на начало символа в строке.
 * Возвращает 1 если найден, продвигает *used на количество прочитанных байт.
 */
static int find_cyr(const char *src, int *row, int *col, int *used)
{
    int i;
    /* Кириллические буквы в UTF-8 занимают 2 байта (диапазон U+0400..U+04FF) */
    /* Пробел — 1 байт */
    for (i = 0; i < CYR_CHARS_USED; i++) {
        int len = (int)strlen(cyr_chars[i]);
        if (strncmp(src, cyr_chars[i], (size_t)len) == 0) {
            *row = i / CYR_SIZE;
            *col = i % CYR_SIZE;
            *used = len;
            return 1;
        }
    }
    return 0;
}

/* =========================================================
 * Определяем язык строки: если встречается кириллица — возвращаем 1
 * ========================================================= */
static int is_cyrillic_text(const char *s)
{
    /* Кириллические UTF-8 символы начинаются с байта 0xD0 или 0xD1 */
    while (*s) {
        unsigned char b = (unsigned char)*s;
        if (b == 0xD0 || b == 0xD1) return 1;
        s++;
    }
    return 0;
}

/* =========================================================
 * polibi — шифрование
 * ========================================================= */
int polibi(const char *plain, char *cipher)
{
    int out_pos = 0;
    int cyr = is_cyrillic_text(plain);
    const char *p = plain;

    cipher[0] = '\0';

    while (*p) {
        int row = 0, col = 0, used = 1;
        int found = 0;

        if (cyr) {
            found = find_cyr(p, &row, &col, &used);
        } else {
            if (isalpha((unsigned char)*p)) {
                found = find_lat(*p, &row, &col);
                used = 1;
            } else {
                /* Незнакомый символ — пропускаем (или копируем как есть) */
                p++;
                continue;
            }
        }

        if (found) {
            /* Запись: "RC " где R и C — цифры 1..SIZE */
            if (out_pos > 0) {
                cipher[out_pos++] = ' ';
            }
            cipher[out_pos++] = (char)('1' + row);
            cipher[out_pos++] = (char)('1' + col);
            cipher[out_pos] = '\0';
        }
        p += used;
    }
    return 0;
}

/* =========================================================
 * depolibi — дешифровка
 * ========================================================= */
int depolibi(const char *cipher, char *plain)
{
    int out_pos = 0;
    const char *p = cipher;

    plain[0] = '\0';

    /* Определяем размер таблицы по максимальной цифре в шифртексте */
    int max_digit = 0;
    const char *scan = cipher;
    while (*scan) {
        if (*scan >= '1' && *scan <= '9') {
            int d = *scan - '0';
            if (d > max_digit) max_digit = d;
        }
        scan++;
    }
    int use_cyr = (max_digit > LAT_SIZE);
    int tsize = use_cyr ? CYR_SIZE : LAT_SIZE;

    while (*p) {
        /* Пропускаем пробелы */
        while (*p == ' ') p++;
        if (!*p) break;

        /* Читаем пару цифр */
        if (*p < '1' || *p > '9') { p++; continue; }
        int row = (*p - '1');
        p++;
        if (*p < '1' || *p > '9') { p++; continue; }
        int col = (*p - '1');
        p++;

        if (row >= tsize || col >= tsize) return -1;

        if (use_cyr) {
            int idx = row * CYR_SIZE + col;
            const char *ch = cyr_chars[idx];
            int len = (int)strlen(ch);
            memcpy(plain + out_pos, ch, (size_t)len);
            out_pos += len;
        } else {
            plain[out_pos++] = lat_table[row][col];
        }
        plain[out_pos] = '\0';
    }
    return 0;
}
