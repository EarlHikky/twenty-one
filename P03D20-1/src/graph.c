#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "func.h"
#include "lex.h"
#include "stack.h"

#define WIDTH 80
#define HEIGHT 25
#define Y_STEP (2.0 / (HEIGHT - 1))
#define X_STEP (4.0 * acos(-1.0) / (WIDTH - 1))
void find_y();
void cleanScreen();
void initDisplay();
void setCursor(int x, int y);
void output(const int *y);
void graph();
void output_with(const int *y);
int main() {
    graph();
    return 0;
}
void graph() {
    initDisplay();
    int y[WIDTH];
    find_y(y);
    output_with(y);
    setCursor(1, HEIGHT + 2);
    getchar();
}
void initDisplay() {
    cleanScreen();
    setCursor(0, 0);
    printf("|");
    for (int i = 0; i < WIDTH; i++) {
        printf("-");
    }
    printf("|");
    setCursor(0, HEIGHT + 1);
    for (int i = 0; i < WIDTH; i++) printf("-");
    printf("-");
    for (int y = 0; y < HEIGHT + 1; y++) {
        setCursor(0, y + 1);
        printf("|");
        setCursor(WIDTH + 1, y + 1);
        printf("|");
    }
    printf("\n");
}
void cleanScreen() {
    printf("\033[2J\033[H");
    setCursor(1, 0);
}

void setCursor(int x, int y) { printf("\033[%d;%dH", y + 1, x + 1); }
void find_y(int y[WIDTH]) {
    double x;
    x = 0;
    int i = 0, out_count;
    char arr[MAX_TOKENS][MAX_TOKENS];
    char expression[MAX_TOKENS];

    read_expression_from_input(expression);

    shunting_yard(expression, arr, &out_count);

    while (x <= 4 * acos(-1.0)) {
        y[i] = round((read_PN(arr, out_count, x) + 1) / (Y_STEP));
        i++;
        x += X_STEP;
    }
}

void output_with(const int *y) {
    for (int j = 0; j < HEIGHT; j++) {
        setCursor(0 + 1, j + 1);
        for (int i = 0; i < WIDTH; i++) {
            if (y[i] == j) {
                printf("*");
            } else {
                printf(".");
            }
        }
    }
}
