#include <ctype.h>
#include <stdio.h>
#include <string.h>
// Определяем количество функций в массиве
#define FUNCTION_COUNT (sizeof(functions) / sizeof(Function))



typedef struct {
    const char *name;
    int len;
} Function;

typedef struct {
    const char *type;
    int priority;
} Operation;

Function functions[] = {
    {"ln", 2},
    {"sin", 3},
    {"cos", 3},
    {"tan", 3},
    {"ctg", 3},
    {"sqrt", 4}
};

Operation functions[] = {
    {"(", 1},
    {")", 1},
    {"*", 2},
    {"/", 2},
    {"+", 3},
    {"-", 3},    
};


int is_digit(char c) { return (c >= '0' && c <= '9'); }

int is_alpha(char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }

int is_function(const char *str, int *len) {
    for (int i = 0; i < FUNCTION_COUNT; i++) {
        if (!strncmp(str, functions[i].name, functions[i].len)) {
            *len = functions[i].len;
            return 1;
        }
    }
    return 0;
}

// int is_function(const char *str, int *len) {
//     if (!strncmp(str, "ln", 2)) {
//         *len = 2;
//         return 1;
//     } else if (!strncmp(str, "sin", 3)) {
//         *len = 3;
//         return 1;
//     } else if (!strncmp(str, "cos", 3)) {
//         *len = 3;
//         return 1;
//     } else if (!strncmp(str, "tan", 3)) {
//         *len = 3;
//         return 1;
//     } else if (!strncmp(str, "ctg", 3)) {
//         *len = 3;
//         return 1;
//     } else if (!strncmp(str, "sqrt", 4)) {
//         *len = 4;
//         return 1;
//     }
//     return 0;
// }

void parse_expression(const char *expression) {
    int i = 0;
    while (expression[i] != '\0') {
        if (is_digit(expression[i])) {
            // Если символ - цифра, собираем число
            printf("Number: ");
            while (is_digit(expression[i])) {
                printf("%c", expression[i]);
                i++;
            }
            printf("\n");
        } else if (is_alpha(expression[i])) {
            // Если это буква, проверяем функцию или переменную
            int func_len = 0;
            if (is_function(&expression[i], &func_len)) {
                printf("Function: ");
                for (int j = 0; j < func_len; j++) {
                    printf("%c", expression[i + j]);
                }
                printf("\n");
                i += func_len;
            } else {
                // Если это переменная, например 'x'
                printf("Variable: %c\n", expression[i]);
                i++;
            }
        } else if (expression[i] == '(' || expression[i] == ')') {
            // Если это скобка
            printf("Parenthesis: %c\n", expression[i]);
            i++;
        } else if (expression[i] == '+' || expression[i] == '*' || expression[i] == '/') {
            // Если это оператор
            printf("Operator: %c\n", expression[i]);
            i++;
        } else {
            // Пропуск пробелов или других незначащих символов
            i++;
        }
    }
}

int main() {
    const char *expression = "sin(3x)*ln(22)*sqrt(16)";
    parse_expression(expression);
    return 0;
}