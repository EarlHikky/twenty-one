#include <stdio.h>
#include <string.h>

#define MAX_TOKENS 100

// Примерный код для стека (простейший стек для строковых данных)
typedef struct {
    char data[MAX_TOKENS][MAX_TOKENS];
    int top;
} stack;

// Инициализация стека
void init_stack(stack* s) {
    s->top = -1;
}

// Проверка, пуст ли стек
int is_empty_lex(stack* s) {
    return s->top == -1;
}

// Добавление элемента в стек
void push_lex(stack* s, const char* value) {
    strcpy(s->data[++(s->top)], value);
}

// Извлечение элемента из стека
void pop_lex(stack* s, char* result) {
    strcpy(result, s->data[(s->top)--]);
}

// Просмотр верхушки стека
const char* peek(stack* s) {
    return s->data[s->top];
}

// Функция, возвращающая приоритет оператора
int get_operator_priority(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

// Демонстрация работы process_operator
void process_operator(const char* expression, int* i, char output[][MAX_TOKENS], int* out_count, stack* op_stack) {
    char top_op[MAX_TOKENS];
    while (!is_empty_lex(op_stack) &&
           get_operator_priority(peek(op_stack)[0]) >= get_operator_priority(expression[*i])) {
        pop_lex(op_stack, top_op);
        strcpy(output[*out_count], top_op);
        (*out_count)++;
    }
    char op[2] = {expression[*i], '\0'};
    push_lex(op_stack, op);
    (*i)++;
}

// Главная функция, демонстрирующая работу
void process_expression(const char* expression) {
    stack op_stack;
    init_stack(&op_stack);

    char output[MAX_TOKENS][MAX_TOKENS];  // Массив для ОПН
    int out_count = 0;
    int i = 0;

    while (expression[i] != '\0') {
        if (expression[i] == '+' || expression[i] == '*' || expression[i] == '/') {
            process_operator(expression, &i, output, &out_count, &op_stack);
        } else {
            // Считаем, что это операнд и просто добавляем его в выходной массив
            char operand[2] = {expression[i], '\0'};
            strcpy(output[out_count++], operand);
            i++;
        }
    }

    // После обработки выражения извлекаем оставшиеся операторы из стека
    while (!is_empty_lex(&op_stack)) {
        char top_op[MAX_TOKENS];
        pop_lex(&op_stack, top_op);
        strcpy(output[out_count++], top_op);
    }

    // Печатаем результат (выражение в ОПН)
    printf("Обратная польская нотация: ");
    for (int j = 0; j < out_count; j++) {
        printf("%s ", output[j]);
    }
    printf("\n");
}

int main() {
    const char* expression = "3+5*2-8/4";  // Пример выражения
    process_expression(expression);
    return 0;
}