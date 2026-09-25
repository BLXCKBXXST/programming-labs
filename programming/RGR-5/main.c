#include <stdio.h>
#include <string.h>
#include "cipher.h"

int main(void)
{
    char plain[MAX_TEXT];
    char encrypted[MAX_ENC];
    char decrypted[MAX_TEXT];

    /* Ввод текста */
    printf("Введите текст (латиница или кириллица): ");
    if (!fgets(plain, sizeof(plain), stdin)) {
        fprintf(stderr, "Ошибка чтения.\n");
        return 1;
    }
    /* Убираем '\n' от fgets */
    plain[strcspn(plain, "\n")] = '\0';

    printf("\n--- Исходный текст ---\n%s\n", plain);

    /* Шифрование */
    if (polibi(plain, encrypted) != 0) {
        fprintf(stderr, "Ошибка шифрования.\n");
        return 1;
    }
    printf("\n--- После шифрования (Polibi) ---\n%s\n", encrypted);

    /* Дешифровка */
    if (depolibi(encrypted, decrypted) != 0) {
        fprintf(stderr, "Ошибка дешифровки.\n");
        return 1;
    }
    printf("\n--- После дешифровки (DePolibi) ---\n%s\n", decrypted);

    /* Проверка совпадения */
    if (strcmp(plain, decrypted) == 0) {
        printf("\n[OK] Исходный текст совпадает с дешифрованным.\n");
    } else {
        printf("\n[FAIL] Тексты НЕ совпадают!\n");
        printf("  Исходный  : %s\n", plain);
        printf("  Дешифрован: %s\n", decrypted);
    }

    return 0;
}
