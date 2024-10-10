/*
Скрипт для обработки матрицы произвольной размерности. Поиска максимальных элементов в строках и минимальных элементов в столбцах.
В зависимости от выбора матрица формируется статически или динамически:

1. Обработка статической матрицы.
2. Обработка через массив указателей на массивы.
3. Обработка через массив указателей и общий буфер.
4. Обработка через массив указателей и один буфер.


*/

#include <stdio.h>
#include <stdlib.h>

#define NMAX 100  // Максимальное количество строк и столбцов для статической матрицы
#define STATIC 1
#define ARRAY_OF_POINTERS_TO_ARRAY 2
#define ARRAY_OF_POINTERS_TO_SECOND_ARRAY 3
#define ARRAY_OF_POINTERS_TO_ARRAY_WITH_ONE_BUFFER 4

int get_choice(void);
int get_shape(unsigned int *rows, unsigned int *cols);
int get_matrix(int **matrix, unsigned int rows, unsigned int cols);
void print_matrix(int **matrix, unsigned int rows, unsigned int cols);
void free_matrix(int **matrix, unsigned int rows);
void find_max_in_rows(int **matrix, unsigned int rows, unsigned int cols, int *max_in_rows);
void find_min_in_cols(int **matrix, unsigned int rows, unsigned int cols, int *min_in_cols);
int handle_matrix_choice(int choice, unsigned int rows, unsigned int cols);
int handle_static_matrix(unsigned int rows, unsigned int cols);
int handle_array_of_pointers_to_array(unsigned int rows, unsigned int cols);
int handle_array_of_pointers_to_second_array(unsigned int rows, unsigned int cols);
int handle_array_of_pointers_to_array_with_one_buffer(unsigned int rows, unsigned int cols);

int main() {
    unsigned int rows, cols;
    int choice = get_choice();

    if (choice < STATIC || choice > ARRAY_OF_POINTERS_TO_ARRAY_WITH_ONE_BUFFER) {
        printf("n/a");
        return 1;
    }

    if (!get_shape(&rows, &cols)) {
        printf("n/a");
        return 1;
    }

    if (!handle_matrix_choice(choice, rows, cols)) {
        printf("n/a");
        return 1;
    }

    return 0;
}

// Функция для получения выбора пользователя
int get_choice(void) {
    int choice = 0;
    char confirm;
    if (scanf("%d%c", &choice, &confirm) != 2 || confirm != '\n') return 0;
    return choice;
}

// Функция для обработки выбора пользователя
int handle_matrix_choice(int choice, unsigned int rows, unsigned int cols) {
    switch (choice) {
        case STATIC:
            return handle_static_matrix(rows, cols);
        case ARRAY_OF_POINTERS_TO_ARRAY:
            return handle_array_of_pointers_to_array(rows, cols);
        case ARRAY_OF_POINTERS_TO_SECOND_ARRAY:
            return handle_array_of_pointers_to_second_array(rows, cols);
        case ARRAY_OF_POINTERS_TO_ARRAY_WITH_ONE_BUFFER:
            return handle_array_of_pointers_to_array_with_one_buffer(rows, cols);
        default:
            return 0;
    }
}

// Функция для обработки статической матрицы
int handle_static_matrix(unsigned int rows, unsigned int cols) {
    if (rows > NMAX || cols > NMAX) {
        return 0;
    }
    int matrix[NMAX][NMAX];
    int *matrix_ptr[NMAX];
    for (unsigned int i = 0; i < rows; i++) {
        matrix_ptr[i] = matrix[i];
    }
    if (!get_matrix(matrix_ptr, rows, cols)) {
        return 0;
    }
    print_matrix(matrix_ptr, rows, cols);

    // Вычисление максимальных и минимальных элементов
    int max_in_rows[NMAX], min_in_cols[NMAX];
    find_max_in_rows(matrix_ptr, rows, cols, max_in_rows);
    find_min_in_cols(matrix_ptr, rows, cols, min_in_cols);

    // Вывод максимальных и минимальных элементов
    for (unsigned int i = 0; i < rows; i++) {
        if (i > 0) printf(" ");
        printf("%d", max_in_rows[i]);
    }
    printf("\n");
    for (unsigned int j = 0; j < cols; j++) {
        if (j > 0) printf(" ");
        printf("%d", min_in_cols[j]);
    }

    return 1;
}

// Функция для обработки через массив указателей на массивы
int handle_array_of_pointers_to_array(unsigned int rows, unsigned int cols) {
    int **matrix = malloc(rows * sizeof(int *));
    for (unsigned int i = 0; i < rows; i++) {
        matrix[i] = malloc(cols * sizeof(int));
    }

    if (!matrix || !get_matrix(matrix, rows, cols)) {
        free_matrix(matrix, rows);
        return 0;
    }

    print_matrix(matrix, rows, cols);

    // Вычисление максимальных и минимальных элементов
    int *max_in_rows = malloc(rows * sizeof(int));
    int *min_in_cols = malloc(cols * sizeof(int));
    find_max_in_rows(matrix, rows, cols, max_in_rows);
    find_min_in_cols(matrix, rows, cols, min_in_cols);

    // Вывод максимальных элементов
    for (unsigned int i = 0; i < rows; i++) {
        if (i > 0) printf(" ");
        printf("%d", max_in_rows[i]);
    }
    printf("\n");

    // Вывод минимальных элементов
    for (unsigned int j = 0; j < cols; j++) {
        if (j > 0) printf(" ");
        printf("%d", min_in_cols[j]);
    }

    free(max_in_rows);
    free(min_in_cols);
    free_matrix(matrix, rows);

    return 1;
}

// Функция для обработки через массив указателей с единым буфером
int handle_array_of_pointers_to_array_with_one_buffer(unsigned int rows, unsigned int cols) {
    int **matrix = malloc(rows * sizeof(int *) + rows * cols * sizeof(int));
    int *buffer = (int *)(matrix + rows);
    for (unsigned int i = 0; i < rows; i++) {
        matrix[i] = buffer + i * cols;
    }

    if (!matrix || !get_matrix(matrix, rows, cols)) {
        free(matrix);
        return 0;
    }

    print_matrix(matrix, rows, cols);

    // Вычисление максимальных и минимальных элементов
    int *max_in_rows = malloc(rows * sizeof(int));
    int *min_in_cols = malloc(cols * sizeof(int));
    find_max_in_rows(matrix, rows, cols, max_in_rows);
    find_min_in_cols(matrix, rows, cols, min_in_cols);

    // Вывод максимальных элементов
    for (unsigned int i = 0; i < rows; i++) {
        if (i > 0) printf(" ");
        printf("%d", max_in_rows[i]);
    }
    printf("\n");

    // Вывод минимальных элементов
    for (unsigned int j = 0; j < cols; j++) {
        if (j > 0) printf(" ");
        printf("%d", min_in_cols[j]);
    }

    free(max_in_rows);
    free(min_in_cols);
    free(matrix);

    return 1;
}

// Функция для обработки через массив указателей и общий буфер
int handle_array_of_pointers_to_second_array(unsigned int rows, unsigned int cols) {
    int **matrix = malloc(rows * sizeof(int *));
    int *buffer = malloc(rows * cols * sizeof(int));
    for (unsigned int i = 0; i < rows; i++) {
        matrix[i] = buffer + i * cols;
    }

    if (!matrix || !get_matrix(matrix, rows, cols)) {
        free(matrix);
        free(buffer);
        return 0;
    }

    print_matrix(matrix, rows, cols);

    // Вычисление максимальных и минимальных элементов
    int *max_in_rows = malloc(rows * sizeof(int));
    int *min_in_cols = malloc(cols * sizeof(int));
    find_max_in_rows(matrix, rows, cols, max_in_rows);
    find_min_in_cols(matrix, rows, cols, min_in_cols);

    // Вывод максимальных элементов
    for (unsigned int i = 0; i < rows; i++) {
        if (i > 0) printf(" ");
        printf("%d", max_in_rows[i]);
    }
    printf("\n");

    // Вывод минимальных элементов
    for (unsigned int j = 0; j < cols; j++) {
        if (j > 0) printf(" ");
        printf("%d", min_in_cols[j]);
    }

    free(max_in_rows);
    free(min_in_cols);
    free(matrix);
    free(buffer);

    return 1;
}

// Функция для получения размеров матрицы
int get_shape(unsigned int *rows, unsigned int *cols) {
    char space, confirm;
    if (scanf("%u%c%u%c", rows, &space, cols, &confirm) != 4 || space != ' ' || confirm != '\n') return 0;
    return 1;
}

// Функция для ввода элементов матрицы
int get_matrix(int **matrix, unsigned int rows, unsigned int cols) {
    for (unsigned int i = 0; i < rows; i++) {
        for (unsigned int j = 0; j < cols; j++) {
            if (scanf("%d", &matrix[i][j]) != 1) {
                return 0;
            }
        }
    }
    return 1;
}

// Функция для вывода матрицы
void print_matrix(int **matrix, unsigned int rows, unsigned int cols) {
    for (unsigned int i = 0; i < rows; i++) {
        for (unsigned int j = 0; j < cols; j++) {
            if (j > 0) printf(" ");
            printf("%d", matrix[i][j]);
        }
        if (i != rows - 1) {
            printf("\n");  // Перенос строки после каждой строки, кроме последней
        }
    }
}

// Функция для освобождения памяти матрицы
void free_matrix(int **matrix, unsigned int rows) {
    for (unsigned int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Функция для поиска максимальных элементов в каждой строке
void find_max_in_rows(int **matrix, unsigned int rows, unsigned int cols, int *max_in_rows) {
    for (unsigned int i = 0; i < rows; i++) {
        int max = matrix[i][0];
        for (unsigned int j = 1; j < cols; j++) {
            if (matrix[i][j] > max) {
                max = matrix[i][j];
            }
        }
        max_in_rows[i] = max;
    }
}

// Функция для поиска минимальных элементов в каждом столбце
void find_min_in_cols(int **matrix, unsigned int rows, unsigned int cols, int *min_in_cols) {
    for (unsigned int j = 0; j < cols; j++) {
        int min = matrix[0][j];
        for (unsigned int i = 1; i < rows; i++) {
            if (matrix[i][j] < min) {
                min = matrix[i][j];
            }
        }
        min_in_cols[j] = min;
    }
}

