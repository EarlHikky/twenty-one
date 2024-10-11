#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPS 1e-6  // Порог для сравнения с нулем

void input(double **matrix, int *n, int *m) {
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *m; j++) {
            scanf("%lf", &matrix[i][j]);
        }
    }
}

void output(double **matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%.6lf", matrix[i][j]);
            if (j < m - 1) {
                printf(" ");
            }
        }
        if (i < n - 1) {
            printf("\n");
        }
    }
}

// Функция для нахождения обратной матрицы методом Гаусса-Жордана
int invert(double **matrix, int n, int m) {
    if (n != m) {
        return 0;  // Обратная матрица может быть только для квадратной матрицы
    }

    double **augmented = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        augmented[i] = (double *)malloc(2 * n * sizeof(double));
        for (int j = 0; j < n; j++) {
            augmented[i][j] = matrix[i][j];  // Копируем оригинальную матрицу
        }
        for (int j = n; j < 2 * n; j++) {
            augmented[i][j] = (i == j - n) ? 1.0 : 0.0;  // Единичная матрица
        }
    }

    // Прямой ход
    for (int i = 0; i < n; i++) {
        if (fabs(augmented[i][i]) < EPS) {
            return 0;  // Если элемент на диагонали нулевой, матрица вырожденная
        }

        double diag = augmented[i][i];
        for (int j = 0; j < 2 * n; j++) {
            augmented[i][j] /= diag;  // Нормализуем текущую строку
        }

        for (int k = 0; k < n; k++) {
            if (k != i) {
                double factor = augmented[k][i];
                for (int j = 0; j < 2 * n; j++) {
                    augmented[k][j] -= factor * augmented[i][j];
                }
            }
        }
    }

    // Копируем обратную матрицу из расширенной матрицы
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = augmented[i][j + n];
        }
        free(augmented[i]);
    }
    free(augmented);

    return 1;  // Успешно нашли обратную матрицу
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    double **matrix = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (double *)malloc(m * sizeof(double));
    }

    input(matrix, &n, &m);

    if (invert(matrix, n, m)) {
        output(matrix, n, n);
    } else {
        printf("n/a");
    }

    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
