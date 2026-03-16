#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Оценка 3: Матрица NxN и её определитель (N от 1 до 3)

int main() {
    int N;
    printf("Введите N (1-3): ");
    scanf("%d", &N);

    if (N < 1 || N > 3) {
        printf("Ошибка: N должно быть от 1 до 3\n");
        return 1;
    }

    int matrix[3][3];
    srand(time(NULL));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            matrix[i][j] = rand() % 19 - 9; // [-9..9]

    printf("\nМатрица %dx%d:\n", N, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%4d", matrix[i][j]);
        printf("\n");
    }

    int det = 0;
    switch (N) {
        case 1:
            det = matrix[0][0];
            break;
        case 2:
            det = matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0];
            break;
        case 3:
            det = matrix[0][0]*matrix[1][1]*matrix[2][2]
                + matrix[0][1]*matrix[1][2]*matrix[2][0]
                + matrix[0][2]*matrix[1][0]*matrix[2][1]
                - matrix[0][2]*matrix[1][1]*matrix[2][0]
                - matrix[0][0]*matrix[1][2]*matrix[2][1]
                - matrix[0][1]*matrix[1][0]*matrix[2][2];
            break;
    }
    printf("\nОпределитель: %d\n", det);
    return 0;
}
