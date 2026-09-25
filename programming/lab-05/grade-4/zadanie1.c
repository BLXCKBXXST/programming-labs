#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Задание на оценку 4: Обработка массива комплексных чисел
// Массив: [RE0, IM0, RE1, IM1, ...] — чётные индексы реальная часть, нечётные — мнимая

int main() {
    int N;
    printf("Введите количество комплексных чисел N: ");
    scanf("%d", &N);

    if (N <= 0) {
        printf("Ошибка: N должно быть больше 0\n");
        return 1;
    }

    float re[N], im[N];

    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        re[i] = (float)(rand() % 65536 - 32768);
        im[i] = (float)(rand() % 65536 - 32768);
    }

    printf("\nЗначения сигнала:\n");
    for (int i = 0; i < N; i++) {
        printf("s[%d] = %.1f + j*(%.1f)\n", i, re[i], im[i]);
    }

    float energy = 0;
    for (int i = 0; i < N; i++) {
        energy += re[i] * re[i] + im[i] * im[i];
    }
    printf("\nЭнергия сигнала: %.1f\n", energy);

    float max_re = re[0];
    for (int i = 1; i < N; i++) {
        if (re[i] > max_re)
            max_re = re[i];
    }
    printf("Максимальный элемент реальной части: %.1f\n", max_re);

    return 0;
}
