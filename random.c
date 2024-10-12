#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#define ROWS 25
#define COLUMNS 80
#define STABLE 1
#define LONG_LIVED 2
#define PERIODIC 3
#define MOVING 4
#define TRAIN 5
#define SLOW 1
#define NORMAL 2
#define FAST 3

void field_init(int field[ROWS][COLUMNS], int choice);
void output(int field[ROWS][COLUMNS]);
int neighbor_count(int field[ROWS][COLUMNS], int ceil_row, int ceil_column);
void refresh_field(int field[ROWS][COLUMNS]);
void show_menu();
void show_speed_menu();
void set_speed(int *speed);

int main() {
    initscr();
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_BLACK);

    int field[ROWS][COLUMNS];
    int gameover = 0;
    int choice = 0;
    int speed = 200;

    show_menu();
    scanw("%d", &choice);

    show_speed_menu();
    scanw("%d", &speed);
    set_speed(&speed);

    field_init(field, choice);

    while (!gameover) {
        napms(speed);
        clear();

        refresh_field(field);
        refresh();
    }
    endwin();

    output(field);
    return 0;
}

void show_menu() {
    printw("Choose init state:\n");
    printw("1. Stable\n");
    printw("2. Long-lived\n");
    printw("3. Periodic\n");
    printw("4. Moving\n");
    printw("5. Train\n");
}

void show_speed_menu() {
    printw("Choose speed:\n");
    printw("1 - Slow\n");
    printw("2 - Normal\n");
    printw("3 - Fast\n");
}

void set_speed(int *speed) {
    switch (*speed) {
        case SLOW:
            *speed = 600;
            break;

        case NORMAL:
            *speed = 200;
            break;

        case FAST:
            *speed = 50;
            break;

        default:
            *speed = 200;
            break;
    }
}

void field_init(int field[ROWS][COLUMNS], int choice) {
    for (int row = 0; row < ROWS; row++) {
        for (int column = 0; column < COLUMNS; column++) {
            field[row][column] = 0;
        }
    }

    switch (choice) {
        case STABLE:
            field[10][10] = 1;
            field[10][11] = 1;
            field[11][10] = 1;
            field[11][11] = 1;
            break;

        case LONG_LIVED:
            field[10][11] = 1;
            field[11][10] = 1;
            field[11][11] = 1;
            field[12][11] = 1;
            break;

        case PERIODIC:
            field[10][12] = field[10][13] = field[10][14] = 1;
            field[10][18] = field[10][19] = field[10][20] = 1;
            field[12][10] = field[13][10] = field[14][10] = 1;
            field[12][15] = field[13][15] = field[14][15] = 1;
            field[12][17] = field[13][17] = field[14][17] = 1;
            field[12][22] = field[13][22] = field[14][22] = 1;
            field[16][12] = field[16][13] = field[16][14] = 1;
            field[16][18] = field[16][19] = field[16][20] = 1;
            break;

        case MOVING:
            field[1][2] = 1;
            field[2][3] = 1;
            field[3][1] = 1;
            field[3][2] = 1;
            field[3][3] = 1;
            break;

        case TRAIN:
            field[1][2] = 1;
            field[1][5] = 1;
            field[2][6] = 1;
            field[3][6] = 1;
            field[4][6] = 1;
            field[4][5] = 1;
            field[4][4] = 1;
            field[4][3] = 1;
            break;

        default:
            int cells = rand() % 100 + 250;
            for (int i = 0; i < cells; i++) {
                int row = rand() % ROWS;
                int column = rand() % COLUMNS;
                field[row][column] = 1;
            }
            break;
    }
}

void output(int field[ROWS][COLUMNS]) {
    for (int row = 0; row < ROWS; row++) {
        for (int column = 0; column < COLUMNS; column++) {
            move(row, column);

            if (field[row][column]) {
                attron(COLOR_PAIR(1));
                printw("0");
                attroff(COLOR_PAIR(1));
            } else {
                attron(COLOR_PAIR(2));
                printw(".");
                attroff(COLOR_PAIR(2));
            }

            if (column < COLUMNS - 1) {
                printw(" ");
            }
        }
        printw("\n");
    }
}

int neighbor_count(int field[ROWS][COLUMNS], int ceil_row, int ceil_column) {
    int count = 0;
    for (int row = -1; row <= 1; row++) {
        for (int column = -1; column <= 1; column++) {
            if (!(row == 0 && column == 0)) {
                int neighbor_row = (ceil_row + row + ROWS) % ROWS;
                int neighbor_column = (ceil_column + column + COLUMNS) % COLUMNS;
                if (field[neighbor_row][neighbor_column]) count++;
            }
        }
    }
    return count;
}

void refresh_field(int field[ROWS][COLUMNS]) {
    int new_field[ROWS][COLUMNS];

    for (int row = 0; row < ROWS; row++) {
        for (int column = 0; column < COLUMNS; column++) {
            int neighbors = neighbor_count(field, row, column);

            if (field[row][column]) {
                if (neighbors == 2 || neighbors == 3) {
                    new_field[row][column] = 1;
                } else {
                    new_field[row][column] = 0;
                }
            } else {
                if (neighbors == 3) {
                    new_field[row][column] = 1;
                } else {
                    new_field[row][column] = 0;
                }
            }
        }
    }

    for (int row = 0; row < ROWS; row++) {
        for (int column = 0; column < COLUMNS; column++) {
            field[row][column] = new_field[row][column];
        }
    }

    // int random_row = rand() % ROWS;
    // int random_column = rand() % COLUMNS;
    // field[random_row][random_column] = 1;

    output(field);
}
