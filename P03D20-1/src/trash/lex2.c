#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char items[MAX][MAX];
    int top;
} Stack;

void init(Stack* stack) { stack->top = -1; }

int is_empty(Stack* stack) { return stack->top == -1; }

void push(Stack* stack, char* value) {
    if (stack->top < MAX - 1) {
        strcpy(stack->items[++stack->top], value);
    }
}

char* pop(Stack* stack) {
    if (!is_empty(stack)) {
        return stack->items[stack->top--];
    }
    return NULL;
}

char* peek(Stack* stack) {
    if (!is_empty(stack)) {
        return stack->items[stack->top];
    }
    return NULL;
}

int precedence(char* op) {
    if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0) {
        return 1;
    }
    if (strcmp(op, "*") == 0 || strcmp(op, "/") == 0) {
        return 2;
    }
    return 0;
}

int is_operator(char* token) {
    return strcmp(token, "+") == 0 || strcmp(token, "-") == 0 || strcmp(token, "*") == 0 ||
           strcmp(token, "/") == 0;
}

int is_digit(char c) { return (c >= '0' && c <= '9'); }

int is_left_parenthesis(char* token) { return strcmp(token, "(") == 0; }

int is_right_parenthesis(char* token) { return strcmp(token, ")") == 0; }

void shunting_yard(char* tokens[], int len, char* output[]) {
    Stack operators;
    init(&operators);
    int out_idx = 0;

    for (int i = 0; i < len; i++) {
        char* token = tokens[i];

        if (is_digit(token[0]) || (token[0] == '-' && is_digit(token[1]))) {
            // Если токен — число, добавляем его в выходную строку
            output[out_idx++] = token;
        } else if (is_operator(token)) {
            // Если токен — оператор
            while (!is_empty(&operators) && is_operator(peek(&operators)) &&
                   precedence(peek(&operators)) >= precedence(token)) {
                output[out_idx++] = pop(&operators);
            }
            push(&operators, token);
        } else if (is_left_parenthesis(token)) {
            // Открывающая скобка всегда идёт в стек
            push(&operators, token);
        } else if (is_right_parenthesis(token)) {
            // Закрывающая скобка вызывает извлечение до первой открывающей скобки
            while (!is_empty(&operators) && !is_left_parenthesis(peek(&operators))) {
                output[out_idx++] = pop(&operators);
            }
            pop(&operators);  // Убираем открывающую скобку из стека
        }
    }

    // Добавляем оставшиеся операторы в выходную строку
    while (!is_empty(&operators)) {
        output[out_idx++] = pop(&operators);
    }
    output[out_idx] = NULL;  // Завершаем вывод нулевым указателем
}

int main() {
    // Пример инфиксного выражения: "3 + 5 * ( 2 - 8 )"
    char* expression[] = {"3", "+", "5", "*", "(", "2", "-", "8", ")", NULL};

    // Массив для результата в ОПН
    char* rpn[MAX];

    // Преобразуем в ОПН
    shunting_yard(expression, 9, rpn);

    // Вывод результата в ОПН
    printf("Reverse Polish Notation: ");
    for (int i = 0; rpn[i] != NULL; i++) {
        printf("%s ", rpn[i]);
    }
    printf("\n");

    return 0;
}
