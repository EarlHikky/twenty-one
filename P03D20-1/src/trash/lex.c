#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
// #include "lex.h"

#define MAX_STACK_SIZE 100

typedef struct {
    char *value;
    struct Token *next;
    int *priority;
} Token;

typedef struct {
    char data[MAX_STACK_SIZE];
    int top;
} Stack;

Token *tokenize(const char *expression, int *token_count) {
    for (int i = 0; expression[i] != '\0'; i++) {
        switch (expression[i]) {
            case '-':
                printf("--- %c\n", expression[i]);
                break;

            case '+':
                printf("+++ %c\n", expression[i]);
                break;

            case '*':
                printf("*** %c\n", expression[i]);
                break;

            case '/':
                printf("/// %c\n", expression[i]);
                break;

            default:
                printf("%c \n", expression[i]);
                break;
        }
    }
}

int main(void) {
    char *test_string = "ln(2-3)*x";
    const char *test_str_sep = "+-*/()";
    const char *istr;

    int *token_count;
    // Token *t1 = tokenize(test_string, token_count);

    istr = strtok(test_string, test_str_sep);

    // Выделение последующих частей
    while (istr != NULL) {
        // Вывод очередной выделенной части
        printf("%s  \n", istr);
        // Выделение очередной части строки
        istr = strtok(NULL, test_str_sep);
    }

    return 0;
}

// Token *tokenize(const char *expression, int *token_count) {
//     Token *tokens = malloc(sizeof(Token) * 100);
//     *token_count = 0;

//     for (int i = 0; expression[i] != '\0'; i++) {
//         if (isdigit(expression[i])) {
//             tokens[*token_count].type = TOKEN_NUMBER;
//             tokens[*token_count].value = strtod(&expression[i], NULL);
//             while (isdigit(expression[i]) || expression[i] == '.') i++;
//             i--;
//             (*token_count)++;
//         } else if (expression[i] == '+' || expression[i] == '-') {
//             if (i == 0 || !isdigit(expression[i-1]) && expression[i-1] != ')') {
//                 tokens[*token_count].type = TOKEN_UNARY_OPERATOR;
//                 tokens[*token_count].op = expression[i];
//             } else {
//                 tokens[*token_count].type = TOKEN_OPERATOR;
//                 tokens[*token_count].op = expression[i];
//             }
//             (*token_count)++;
//         } else if (strchr("*/", expression[i])) {
//             tokens[*token_count].type = TOKEN_OPERATOR;
//             tokens[*token_count].op = expression[i];
//             (*token_count)++;
//         } else if (expression[i] == '(') {
//             tokens[*token_count].type = TOKEN_LEFT_PAREN;
//             (*token_count)++;
//         } else if (expression[i] == ')') {
//             tokens[*token_count].type = TOKEN_RIGHT_PAREN;
//             (*token_count)++;
//         } else if (strncmp(&expression[i], "sin", 3) == 0) {
//             tokens[*token_count].type = TOKEN_FUNCTION;
//             strcpy(tokens[*token_count].func, "sin");
//             i += 2;
//             (*token_count)++;
//         } else if (strncmp(&expression[i], "cos", 3) == 0) {
//             tokens[*token_count].type = TOKEN_FUNCTION;
//             strcpy(tokens[*token_count].func, "cos");
//             i += 2;
//             (*token_count)++;
//         }
//     }
//     return tokens;
// }

// void push(Stack *s, char c) {
//     if (s->top < MAX_STACK_SIZE - 1) {
//         s->data[++(s->top)] = c;
//     }
// }

// char pop(Stack *s) {
//     if (s->top >= 0) {
//         return s->data[(s->top)--];
//     }
//     return '\0';  // пустой символ, если стек пуст
// }

// char peek(Stack *s) {
//     if (s->top >= 0) {
//         return s->data[s->top];
//     }
//     return '\0';
// }

// int precedence(char operator) {
//     switch (operator) {
//         case '+':
//         case '-':
//             return 1;
//         case '*':
//         case '/':
//             return 2;
//         default:
//             return 0;
//     }
// }

// // Функция для преобразования выражения в обратную польскую нотацию
// void to_reverse_polish(const char *expression) {
//     Stack operator_stack = {.top = -1};
//     char output[100] = "";
//     int j = 0;

//     for (int i = 0; expression[i] != '\0'; i++) {
//         char token = expression[i];

//         if (isdigit(token)) {
//             // Если это цифра, просто добавляем ее к выходной строке
//             output[j++] = token;
//             output[j++] = ' ';  // разделитель между операндами
//         } else if (token == '(') {
//             // Если это открывающая скобка, помещаем ее в стек
//             push(&operator_stack, token);
//         } else if (token == ')') {
//             // Если это закрывающая скобка, выталкиваем все операторы до открывающей скобки
//             while (peek(&operator_stack) != '(') {
//                 output[j++] = pop(&operator_stack);
//                 output[j++] = ' ';
//             }
//             pop(&operator_stack);  // удаляем '('
//         } else if (token == '+'⠺⠵⠵⠵⠟⠟⠵⠵⠟⠟⠟⠵⠺⠵⠵⠞token == '*' || token == '/') {
//             // Если это оператор, сравниваем приоритет
//             while (precedence(peek(&operator_stack)) >= precedence(token)) {
//                 output[j++] = pop(&operator_stack);
//                 output[j++] = ' ';
//             }
//             push(&operator_stack, token);
//         }
//     }

//     // Выталкиваем все оставшиеся операторы из стека
//     while (operator_stack.top != -1) {
//         output[j++] = pop(&operator_stack);
//         output[j++] = ' ';
//     }

//     printf("Reverse Polish Notation: %s\n", output);
// }

// int main() {
//     const char *expression = "3 + 5 * ( 2 - 8 )";
//     to_reverse_polish(expression);

//     return 0;
// }