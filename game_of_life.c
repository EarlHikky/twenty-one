#include <stdio.h>    // Для функций printf и scanf
#include <stdlib.h>   // Для функции system("clear") (очистка экрана)
#include <unistd.h>   // Для функции usleep (задержка в микросекундах)
void initialize_grid(int rows, int cols, int grid[rows][cols]);
void print_grid(int rows, int cols, int grid[rows][cols]);
int count_neighbors(int rows, int cols, int grid[rows][cols], int x, int y);
void update_grid(int rows, int cols, int grid[rows][cols]);



int main() {
    int rows = 20, cols = 20;
    int grid[20][20];

    // Инициализация игрового поля
    initialize_grid(rows, cols, grid);

    // Цикл игры
    for (int i = 0; i < 100; i++) {  // Цикл на 100 шагов
        system("clear");  // Очищаем экран (в UNIX-системах)
        print_grid(rows, cols, grid);
        update_grid(rows, cols, grid);
        usleep(200000);  // Задержка в 200 миллисекунд
    }

    return 0;
}

void initialize_grid(int rows, int cols, int grid[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid[i][j] = 0;  // По умолчанию все клетки мертвые
        }
    }
    
    // Пример установки нескольких живых клеток
    grid[1][2] = 1;
    grid[2][3] = 1;
    grid[3][1] = 1;
    grid[3][2] = 1;
    grid[3][3] = 1;
}

void print_grid(int rows, int cols, int grid[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == 1) {
                printf("O ");  // Живая клетка
            } else {
                printf(". ");  // Мертвая клетка
            }
        }
        printf("\n");
    }
}

int count_neighbors(int rows, int cols, int grid[rows][cols], int x, int y) {
    int count = 0;

    // Перебор всех соседей
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;  // Пропускаем саму клетку
            int new_x = x + i;
            int new_y = y + j;

            // Проверяем, находится ли сосед в пределах поля
            if (new_x >= 0 && new_x < rows && new_y >= 0 && new_y < cols) {
                count += grid[new_x][new_y];  // Считаем только живые клетки
            }
        }
    }

    return count;
}

void update_grid(int rows, int cols, int grid[rows][cols]) {
    int new_grid[rows][cols];

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int neighbors = count_neighbors(rows, cols, grid, i, j);

            if (grid[i][j] == 1) {
                if (neighbors < 2 || neighbors > 3) {
                    new_grid[i][j] = 0;  // Клетка умирает
                } else {
                    new_grid[i][j] = 1;  // Клетка остаётся живой
                }
            } else {
                if (neighbors == 3) {
                    new_grid[i][j] = 1;  // Клетка оживает
                } else {
                    new_grid[i][j] = 0;  // Клетка остаётся мертвой
                }
            }
        }
    }

    // Копируем новое поле в текущее
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid[i][j] = new_grid[i][j];
        }
    }
}