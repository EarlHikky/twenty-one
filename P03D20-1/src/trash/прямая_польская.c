#include <stdio.h>
#include <string.h>

#define MAX_TOKENS 100
#define FUNCTION_COUNT (sizeof(functions) / sizeof(Function))
#define OPERATOR_COUNT (sizeof(operations) / sizeof(Operation))

typedef struct {
    const char *name;
    int len;
} Function;

typedef struct {
    const char *symbol;
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

Operation operations[] = {
    {"(", 0},
    {")", 0},
    {"*", 2},
    {"/", 2},
    {"+", 1},
    {"-", 1}
};

int is_digit(char c) {
    return (c >= '0' && c <= '9');
}

int is_alpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int is_function(const char *str, int *len) {
    for (int i = 0; i < FUNCTION_COUNT; i++) {
        if (!strncmp(str, functions[i].name, functions[i].len)) {
            *len = functions[i].len;
            return 1;
        }
    }
    return 0;
}

int is_operator(const char *str) {
    for (int i = 0; i < OPERATOR_COUNT; i++) {
        if (*str == *operations[i].symbol) {
            return 1;
        }
    }
    return 0;
}

int get_operator_priority(char op) {
    for (int i = 0; i < OPERATOR_COUNT; i++) {
        if (op == *operations[i].symbol) {
            return operations[i].priority;
        }
    }
    return -1;
}

// Алгоритм для прямой (префиксной) польской нотации
void shunting_yard_prefix(const char *expression, char output[][MAX_TOKENS], int *out_count) {
    char stack[MAX_TOKENS][MAX_TOKENS];  // Стек для операторов
    int stack_top = -1;  // Индекс вершины стека

    int i = 0;
    while (expression[i] != '\0') {
        if (is_digit(expression[i])) {
            // Если цифра, записываем в выходной массив
            int j = 0;
            while (is_digit(expression[i])) {
                output[*out_count][j++] = expression[i++];
            }
            output[*out_count][j] = '\0';
            (*out_count)++;
        } else if (is_alpha(expression[i])) {
            // Если это функция или переменная
            int func_len = 0;
            if (is_function(&expression[i], &func_len)) {
                // Если это функция, сразу добавляем в выходной массив
                strncpy(output[*out_count], &expression[i], func_len);
                output[*out_count][func_len] = '\0'; // Завершаем строку нулём
                (*out_count)++;
                i += func_len;
            } else {
                // Если переменная, добавляем её в выходной массив
                output[*out_count][0] = expression[i++];
                output[*out_count][1] = '\0';
                (*out_count)++;
            }
        } else if (expression[i] == '(') {
            // Если открывающая скобка, добавляем в стек
            strncpy(stack[++stack_top], "(", 1);
            stack[stack_top][1] = '\0';
            i++;
        } else if (expression[i] == ')') {
            // Если закрывающая скобка, выгружаем операторы из стека до открывающей скобки
            while (stack_top >= 0 && strcmp(stack[stack_top], "(") != 0) {
                strcpy(output[*out_count], stack[stack_top--]);
                (*out_count)++;
            }
            if (stack_top >= 0) stack_top--; // Удаляем открывающую скобку
            i++;
        } else if (is_operator(&expression[i])) {
            // Если оператор, добавляем его перед операндами
            while (stack_top >= 0 && get_operator_priority(stack[stack_top][0]) > get_operator_priority(expression[i])) {
                strcpy(output[*out_count], stack[stack_top--]);
                (*out_count)++;
            }
            // Кладём текущий оператор в стек
            strncpy(stack[++stack_top], &expression[i], 1);
            stack[stack_top][1] = '\0';
            i++;
        } else {
            i++;  // Пропуск незначащих символов (например, пробелов)
        }
    }
    // Выталкиваем оставшиеся операторы из стека
    while (stack_top >= 0) {
        strcpy(output[*out_count], stack[stack_top--]);
        (*out_count)++;
    }
}

void print_polish_notation(char output[][MAX_TOKENS], int count) {
    for (int i = 0; i < count; i++) {
        printf("%s ", output[i]);
    }
    printf("\n");
}

int main() {
    // const char *expression = "sin(3*x)+ln(22)/sqrt(16)-42";
    const char *expression = "a+(b-c)*d";
    
    char output[MAX_TOKENS][MAX_TOKENS];  // Массив для префиксной польской нотации
    int out_count = 0;

    shunting_yard_prefix(expression, output, &out_count);

    printf("Prefix Polish Notation: ");
    print_polish_notation(output, out_count);

    return 0;
}