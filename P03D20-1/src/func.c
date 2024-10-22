#include "func.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lex.h"
#include "stack.h"

int is_operator(char a) { return ((int)a > 41 && (int)a < 48 && (int)a != 44 && (int)a != 46); }
int is_number(char a) { return ((int)a > 47 && (int)a < 58); }
int is_func(char *a) {
    return (strcmp(a, "sin") == 0) || (strcmp(a, "tan") == 0) || (strcmp(a, "cos") == 0) ||
           (strcmp(a, "ctg") == 0) || (strcmp(a, "sqrt") == 0) || (strcmp(a, "ln") == 0);
}
double read_PN(char arr[][MAX_TOKENS], int len, double x) {
    struct stack *stack_numbers = init();
    double result;
    int flag = 0;
    for (int i = 0; i < len && flag == 0; i++) {
        if ((arr[i][0]) == 'x' || is_number(arr[i][0]) || (arr[i][0] == '-' && strlen(arr[i]) > 1)) {
            if ((arr[i][0]) == 'x') {
                push(stack_numbers, x);
            } else {
                push(stack_numbers, read_number(arr[i]));
            }
        } else if (is_operator(arr[i][0])) {
            push(stack_numbers, read_opp(arr[i], stack_numbers, &flag));
        } else if (is_func(arr[i])) {
            push(stack_numbers, read_function(arr[i], stack_numbers, &flag));
        } else {
            fprintf(stderr, "Error: Unknown token %s\n", arr[i]);
            destroy(stack_numbers);
            exit(EXIT_FAILURE);
        }
    }
    if (flag == 0) {
        result = pop(stack_numbers);
    } else {
        result = -10;
    }
    destroy(stack_numbers);
    return result;
}
double read_number(char *arr) { return strtod(arr, NULL); }
double read_function(char *arr, struct stack *numbers, int *flag) {
    double result = 1;
    double num = pop(numbers);
    if (strcmp(arr, "sin") == 0) {
        // result = sin with top of stack
        result = sin(num);
    } else if (strcmp(arr, "tan") == 0) {
        // result = tan with top of stack
        if (fabs(cos(num)) > 1E-6) {
            result = tan(num);
        } else {
            *flag = 1;
        }
    } else if (strcmp(arr, "cos") == 0) {
        // result = cos with top of stack
        result = cos(num);
    } else if (strcmp(arr, "ctg") == 0) {
        // result = ctg with top of stack
        if (fabs(sin(num)) > 1E-6) {
            result = 1 / tan(num);
        } else {
            *flag = 1;
        }
    } else if (strcmp(arr, "sqrt") == 0) {
        // result = sqrt with top of stack
        if (num >= 0) {
            result = sqrt(num);
        } else {
            *flag = 1;
        }
    } else if (strcmp(arr, "ln") == 0) {
        // result = ln with top of stack
        if (num > 1E-6) {
            result = log(num);
        } else {
            *flag = 1;
        }
    }
    return result;
}
double read_opp(char *arr, struct stack *numbers, int *flag) {
    // top = top of stack, del top of stack
    // under = new top of stack, del top of stack
    double result = 0;
    double top = pop(numbers);
    double under = pop(numbers);
    // printf("%lf %lf", top, under);
    switch (arr[0]) {
        case '+':
            // under + top
            // printf("+");
            result = under + top;
            break;

        case '-':
            printf("-");
            result = under - top;

            // under - top
            break;

        case '*':
            // under * top
            printf("*");
            result = under * top;
            break;

        case '/':
            // under / top
            printf("*");
            if (fabs(top) > 1E-6) {
                result = under / top;
            } else {
                *flag = 1;
            }

            break;

        default:
            break;
    }
    // printf("%lf", result);
    return result;
}
