#include <stdio.h>
#include <stdlib.h>

int** allocate_matrix(int NomStr, int NomStlb) {
    if (NomStr <= 0 || NomStlb <= 0) return NULL;
    int **matrix = (int**)malloc(NomStr * sizeof(int*));
    if (!matrix) return NULL;
    for (int i = 0; i < NomStr; i++) {
        matrix[i] = (int*)malloc(NomStlb * sizeof(int));
        if (!matrix[i]) {
            for (int prev_str = 0; prev_str < i; prev_str++) 
                free(matrix[prev_str]);
            free(matrix);
            return NULL;
        }
    }
    return matrix;
}

void free_matrix(int **matrix, int NomStr) {
    if (!matrix) return;
    for (int i = 0; i < NomStr; i++) 
        free(matrix[i]);
    free(matrix);
}

void enter_matrix(int **matrix, int NomStr, int NomStlb) {
    for (int i = 0; i < NomStr; i++)
        for (int j = 0; j < NomStlb; j++)
            scanf("%d", &matrix[i][j]);
}

void print_matrix(int **matrix, int NomStr, int NomStlb) {
    for (int i = 0; i < NomStr; i++) {
        for (int j = 0; j < NomStlb; j++) {
            printf("%d%c", matrix[i][j], 
                   j + 1 == NomStlb ? '\n' : ' ');
        }
    }
}

void find_max_position(int **matrix, int NomStr, int NomStlb, 
                      int *max_i, int *max_j) {
    int max_str = 0, max_stlb = 0, max_value = matrix[0][0];
    for (int i = 0; i < NomStr; i++)
        for (int j = 0; j < NomStlb; j++)
            if (matrix[i][j] > max_value) { 
                max_value = matrix[i][j]; 
                max_str = i; 
                max_stlb = j; 
            }
    *max_i = max_str; 
    *max_j = max_stlb;
}

int** create_minor_matrix(int **original_matrix, int orig_kol_str, int orig_kol_stlb, 
                         int remove_str, int remove_stlb, 
                         int *minor_str, int *minor_stlb) {
    if (orig_kol_str <= 1 || orig_kol_stlb <= 1) { 
        *minor_str = 0; 
        *minor_stlb = 0; 
        return NULL; 
    }
    *minor_str = orig_kol_str - 1; 
    *minor_stlb = orig_kol_stlb - 1;
    int **minor_matrix = allocate_matrix(*minor_str, *minor_stlb);
    if (!minor_matrix) return NULL;
    
    int minor_i = 0;
    for (int orig_str = 0; orig_str < orig_kol_str; orig_str++) {
        if (orig_str == remove_str) continue;
        int minor_j = 0;
        for (int orig_stlb = 0; orig_stlb < orig_kol_stlb; orig_stlb++) {
            if (orig_stlb == remove_stlb) continue;
            minor_matrix[minor_i][minor_j++] = original_matrix[orig_str][orig_stlb];
        }
        minor_i++;
    }
    return minor_matrix;
}

int count_str_with_zeros(int **matrix, int NomStr, int NomStlb) {
    int zero_str_counter = 0;
    for (int i = 0; i < NomStr; i++) {
        int zero = 0;
        for (int j = 0; j < NomStlb; j++) {
            if (matrix[i][j] == 0) { 
                zero = 1; 
                break; 
            }
        }
        if (zero) zero_str_counter++;
    }
    return zero_str_counter;
}

void print_minor_diagonal_reversed(int **matrix, int NomStr, int NomStlb) {
    int diagonal_length = (NomStr < NomStlb) ? NomStr : NomStlb;
    for (int diag_index = diagonal_length - 1; diag_index >= 0; diag_index--) {
        printf("%d%c", matrix[diag_index][diag_index], 
               diag_index == 0 ? '\n' : ' ');
    }
}

int main(void) {
    int kolv_str, kolv_stlb;
    if (scanf("%d %d", &kolv_str, &kolv_stlb) != 2 || 
        kolv_str < 1 || kolv_stlb < 1) return 0;

    int **original_matrix = allocate_matrix(kolv_str, kolv_stlb);
    if (!original_matrix) return 0;
    enter_matrix(original_matrix, kolv_str, kolv_stlb);

    int max_i, max_j;
    find_max_position(original_matrix, kolv_str, kolv_stlb, 
                     &max_i, &max_j);

    int minor_kol_str, minor_kol_stlb;
    int **minor_matrix = create_minor_matrix(original_matrix, kolv_str, kolv_stlb,
                                           max_i, max_j,
                                           &minor_kol_str, &minor_kol_stlb);

    if (minor_matrix && minor_kol_str > 0 && minor_kol_stlb > 0) {
        print_matrix(minor_matrix, minor_kol_str, minor_kol_stlb);
        printf("%d\n", count_str_with_zeros(minor_matrix, minor_kol_str, minor_kol_stlb));
        print_minor_diagonal_reversed(minor_matrix, minor_kol_str, minor_kol_stlb);
    } else {
        printf("0\n");
    }

    free_matrix(minor_matrix, minor_kol_str);
    free_matrix(original_matrix, kolv_str);
    return 0;
}
