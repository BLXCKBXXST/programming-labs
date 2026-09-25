#include <stdio.h>
#include <limits.h>

#define MAXN 200

int main(void) {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) {
        return 0;
    }
    if (n < 1 || m < 1 || n > MAXN || m > MAXN) {
        return 0;
    }

    int A[MAXN][MAXN];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    int maxv = A[0][0], r = 0, c = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (A[i][j] > maxv) {
                maxv = A[i][j];
                r = i; c = j;
            }
        }
    }

    int nb = n - 1, mb = m - 1;
    int B[MAXN][MAXN];
    int bi = 0;
    for (int i = 0; i < n; i++) {
        if (i == r) continue;
        int bj = 0;
        for (int j = 0; j < m; j++) {
            if (j == c) continue;
            B[bi][bj++] = A[i][j];
        }
        bi++;
    }

    int rows_with_zero = 0;
    for (int i = 0; i < nb; i++) {
        int has_zero = 0;
        for (int j = 0; j < mb; j++) {
            if (B[i][j] == 0) { has_zero = 1; break; }
        }
        if (has_zero) rows_with_zero++;
    }

    for (int i = 0; i < nb; i++) {
        for (int j = 0; j < mb; j++) {
            printf("%d%c", B[i][j], j + 1 == mb ? '\n' : ' ');
        }
    }

    printf("%d\n", rows_with_zero);

    int len = nb < mb ? nb : mb;
    for (int k = len - 1; k >= 0; k--) {
        printf("%d%c", B[k][k], k == 0 ? '\n' : ' ');
    }

    return 0;
}
