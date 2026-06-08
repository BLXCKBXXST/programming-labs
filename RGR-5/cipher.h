#ifndef CIPHER_H
#define CIPHER_H

/* Максимальная длина строки */
#define MAX_TEXT  512
/* Размер зашифрованного буфера (каждый символ -> 2 цифры + разделитель) */
#define MAX_ENC   (MAX_TEXT * 3)

/* Таблица латиница 5x5 (25 букв, I=J) */
#define LAT_SIZE 5
extern const char lat_table[LAT_SIZE][LAT_SIZE];

/* Таблица кириллица 6x6 (32 буквы + ё убрана, ъ убрана = 30 + пробел + доп) */
#define CYR_SIZE 6
extern const char cyr_table[CYR_SIZE][CYR_SIZE][3]; /* UTF-8 кириллица 2 байта */

/*
 * Шифрование текста по квадрату Полибия.
 * plain  - исходный текст (нуль-терминированная строка)
 * cipher - выходной буфер для шифртекста (числовые пары, разделённые пробелами)
 * Возвращает 0 при успехе, -1 при ошибке.
 */
int polibi(const char *plain, char *cipher);

/*
 * Дешифровка текста по квадрату Полибия.
 * cipher - зашифрованный текст (числовые пары, разделённые пробелами)
 * plain  - выходной буфер для открытого текста
 * Возвращает 0 при успехе, -1 при ошибке.
 */
int depolibi(const char *cipher, char *plain);

#endif /* CIPHER_H */
