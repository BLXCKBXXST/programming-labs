#include <stdio.h>

// Бонус (*): Проверка решения судоку 9x9

#define SIZE 9

int check_rows(int grid[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        int seen[SIZE + 1] = {0};
        for (int j = 0; j < SIZE; j++) {
            int v = grid[i][j];
            if (v < 1 || v > 9 || seen[v]) {
                printf("Ошибка в строке %d\n", i + 1);
                return 0;
            }
            seen[v] = 1;
        }
    }
    return 1;
}

int check_columns(int grid[SIZE][SIZE]) {
    for (int j = 0; j < SIZE; j++) {
        int seen[SIZE + 1] = {0};
        for (int i = 0; i < SIZE; i++) {
            int v = grid[i][j];
            if (v < 1 || v > 9 || seen[v]) {
                printf("Ошибка в столбце %d\n", j + 1);
                return 0;
            }
            seen[v] = 1;
        }
    }
    return 1;
}

int check_squares(int grid[SIZE][SIZE]) {
    for (int bi = 0; bi < 3; bi++) {
        for (int bj = 0; bj < 3; bj++) {
            int seen[SIZE + 1] = {0};
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    int v = grid[bi*3 + i][bj*3 + j];
                    if (v < 1 || v > 9 || seen[v]) {
                        printf("Ошибка в квадрате [%d][%d]\n", bi + 1, bj + 1);
                        return 0;
                    }
                    seen[v] = 1;
                }
            }
        }
    }
    return 1;
}

int is_valid_sudoku(int grid[SIZE][SIZE]) {
    return check_rows(grid) && check_columns(grid) && check_squares(grid);
}

void print_grid(int grid[SIZE][SIZE]) {
    printf("+-------+-------+-------+\n");
    for (int i = 0; i < SIZE; i++) {
        printf("| ");
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", grid[i][j]);
            if (j == 2 || j == 5) printf("| ");
        }
        printf("|\n");
        if (i == 2 || i == 5) printf("+-------+-------+-------+\n");
    }
    printf("+-------+-------+-------+\n");
}

int main() {
    // валидное судоку
    int sudoku[SIZE][SIZE] = {
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 9}
    };

    // невалидное судоку (повтор в строке 1)
    int invalid[SIZE][SIZE] = {
        {5, 5, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 9}
    };

    printf("=== Тест 1: валидное судоку ===\n");
    print_grid(sudoku);
    printf("Результат: %s\n\n",
           is_valid_sudoku(sudoku) ? "ДА, судоку решено верно" : "НЕТ, ошибка в решении");

    printf("=== Тест 2: невалидное судоку ===\n");
    print_grid(invalid);
    printf("Результат: %s\n",
           is_valid_sudoku(invalid) ? "ДА, судоку решено верно" : "НЕТ, ошибка в решении");

    return 0;
}
