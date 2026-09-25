/*
 * task5 — криптографические алгоритмы. Найденные и исправленные баги:
 *
 *  1. xor_encrypt: цикл i <= text_len → off-by-one, читает/пишет за границу.
 *     Также не ставится терминальный '\0' → printf("%s") выводит мусор.
 *
 *  2. caesar_cipher: условие text[i] > 'a' && text[i] < 'z' пропускает
 *     края 'a' и 'z'. Также shift может быть отрицательным, тогда (% 26)
 *     даёт отрицательное число. Не ставится '\0' в конце.
 *
 *  3. vigenere_encrypt: ключ в верхнем регистре, а shift = key[i] - 'a'
 *     (нужно 'A'). Сложение text[i] + shift без модуля 26 — символ
 *     может уйти за пределы алфавита.
 *
 *  4. simple_rc4: первый цикл инициализации шёл до 256+32 → обращение
 *     к S[256..287] (за границу массива). Второй цикл k <= data_len —
 *     off-by-one.
 *
 *  5. simple_hash: sizeof(str) — размер указателя (8 на x64), а не
 *     длина строки. Нужно strlen(str). Плюс <= → off-by-one.
 *
 *  6. generate_key: i <= length пишет за границу буфера, плюс не ставится
 *     терминальный '\0'.
 *
 * Найдено: AddressSanitizer (off-by-one записи и чтения), плюс ручной
 * разбор ожидаемого вывода против реального.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

void xor_encrypt(char *text, char *key, char *output) {
    int text_len = strlen(text);
    int key_len = strlen(key);

    for (int i = 0; i < text_len; i++) {            /* было: i <= text_len */
        output[i] = text[i] ^ key[i % key_len];
    }
    output[text_len] = '\0';                         /* было: терминатор не ставился */
}

void caesar_cipher(char *text, int shift, char *output) {
    int len = strlen(text);
    int s = ((shift % 26) + 26) % 26;                /* нормализуем для отрицательного shift */

    for (int i = 0; i < len; i++) {
        if (text[i] >= 'a' && text[i] <= 'z') {      /* было: > 'a' && < 'z' */
            output[i] = ((text[i] - 'a' + s) % 26) + 'a';
        } else if (text[i] >= 'A' && text[i] <= 'Z') {
            output[i] = ((text[i] - 'A' + s) % 26) + 'A';
        } else {
            output[i] = text[i];
        }
    }
    output[len] = '\0';                              /* было: не ставился */
}

void vigenere_encrypt(char *text, char *keyword, char *output) {
    int text_len = strlen(text);
    int key_len = strlen(keyword);
    int key_index = 0;

    for (int i = 0; i < text_len; i++) {
        if (isalpha((unsigned char)text[i])) {
            /* ключ может быть в любом регистре */
            char k = keyword[key_index % key_len];
            int shift = isupper((unsigned char)k) ? (k - 'A') : (k - 'a');
            char base = isupper((unsigned char)text[i]) ? 'A' : 'a';
            output[i] = ((text[i] - base + shift) % 26) + base;   /* было: text[i] + shift */
            key_index++;
        } else {
            output[i] = text[i];
        }
    }
    output[text_len] = '\0';
}

void simple_rc4(char *key, int key_len, char *data, int data_len) {
    unsigned char S[256];
    unsigned char temp;
    int i, j = 0;

    for (i = 0; i < 256; i++) {
        S[i] = (unsigned char)i;
    }

    for (i = 0; i < 256; i++) {                      /* было: i < 256 + 32 → out-of-bounds */
        j = (j + S[i] + (unsigned char)key[i % key_len]) % 256;
        temp = S[i]; S[i] = S[j]; S[j] = temp;
    }

    i = 0; j = 0;
    for (int k = 0; k < data_len; k++) {             /* было: k <= data_len */
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        temp = S[i]; S[i] = S[j]; S[j] = temp;
        data[k] = data[k] ^ S[(S[i] + S[j]) % 256];
    }
}

unsigned int simple_hash(char *str) {
    unsigned int hash = 0;
    int len = strlen(str);                           /* было: sizeof(str) — размер указателя */

    for (int i = 0; i < len; i++) {                  /* было: i <= sizeof(str) */
        hash += (unsigned char)str[i] * (i + 1) + 50;
    }

    return hash;
}

void generate_key(char *key, int length) {
    /* srand вызываем один раз в main, чтобы повторные вызовы давали разные ключи */
    for (int i = 0; i < length - 1; i++) {           /* было: i <= length, без места под '\0' */
        key[i] = 'a' + (rand() % 26);
    }
    key[length - 1] = '\0';
}

/* ============= ТЕСТОВЫЕ ФУНКЦИИ ============= */

void test_xor_cipher(void) {
    printf("\n=== Test 0: XOR Cipher ===\n");
    char text[] = "Hello World";
    char key[] = "secret";
    int text_len = (int)strlen(text);
    int key_len = (int)strlen(key);
    char output[32];

    /* шифруем побайтово, не полагаясь на strlen в шифре (внутри могут быть '\0') */
    for (int i = 0; i < text_len; i++) {
        output[i] = text[i] ^ key[i % key_len];
    }

    printf("Original: %s\n", text);
    printf("Encrypted: ");
    for (int i = 0; i < text_len; i++) {
        printf("%02X ", (unsigned char)output[i]);
    }
    printf("\n");

    /* дешифрование с известной длиной — иначе '\0' внутри шифра оборвёт strlen */
    char decrypted[32];
    for (int i = 0; i < text_len; i++) {
        decrypted[i] = output[i] ^ key[i % key_len];
    }
    decrypted[text_len] = '\0';
    printf("Decrypted: %s\n", decrypted);
}

void test_caesar_cipher(void) {
    printf("\n=== Test 1: Caesar Cipher ===\n");
    char text[] = "The quick brown fox jumps over the lazy dog";
    char output[64];

    caesar_cipher(text, 3, output);
    printf("Original: %s\n", text);
    printf("Encrypted: %s\n", output);

    char decrypted[64];
    caesar_cipher(output, -3, decrypted);
    printf("Decrypted: %s\n", decrypted);
}

void test_vigenere_cipher(void) {
    printf("\n=== Test 2: Vigenere Cipher ===\n");
    char text[] = "ATTACKATDAWN";
    char keyword[] = "LEMON";
    char output[64];

    vigenere_encrypt(text, keyword, output);
    printf("Original: %s\n", text);
    printf("Keyword: %s\n", keyword);
    printf("Encrypted: %s\n", output);
}

void test_rc4_cipher(void) {
    printf("\n=== Test 3: RC4-like Cipher ===\n");
    char key[] = "Key";
    char data[] = "Secret message";
    int data_len = strlen(data);

    printf("Original: %s\n", data);
    simple_rc4(key, strlen(key), data, data_len);
    printf("Encrypted: ");
    for (int i = 0; i < data_len; i++) {
        printf("%02X ", (unsigned char)data[i]);
    }
    printf("\n");

    simple_rc4(key, strlen(key), data, data_len);
    printf("Decrypted: %s\n", data);
}

void test_hash_function(void) {
    printf("\n=== Test 4: Simple Hash ===\n");
    char *strings[] = {"Hello", "World", "HelloWorld", "Test"};

    for (int i = 0; i < 4; i++) {
        unsigned int hash = simple_hash(strings[i]);
        printf("Hash of \"%s\": %u\n", strings[i], hash);
    }
}

void test_key_generation(void) {
    printf("\n=== Test 5: Key Generation ===\n");
    char key[11];
    generate_key(key, 11);
    printf("Generated key: %s\n", key);

    generate_key(key, 11);
    printf("Another key:   %s\n", key);
}

int main(void) {
    srand((unsigned)time(NULL));

    printf("========================================\n");
    printf("CRYPTOGRAPHY DEBUGGING PRACTICE (fixed)\n");
    printf("========================================\n");

    test_xor_cipher();
    test_caesar_cipher();
    test_vigenere_cipher();
    test_rc4_cipher();
    test_hash_function();
    test_key_generation();

    return 0;
}
