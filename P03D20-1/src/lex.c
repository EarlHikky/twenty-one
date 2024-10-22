#include "lex.h"

#include "stack_lex.h"

Function functions[] = {{"ln", 2}, {"sin", 3}, {"cos", 3}, {"tan", 3}, {"ctg", 3}, {"sqrt", 4}};

Operation operations[] = {{"(", 0}, {")", 0}, {"*", 2}, {"/", 2}, {"+", 1}, {"-", 1}};

int is_digit(char c) { return (c >= '0' && c <= '9'); }

int is_alpha(char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }

/**
 * Checks if given string is a function.
 * If yes, sets the length of the function to the given pointer.
 * @param str String to check.
 * @param len Pointer to the length of the function.
 * @return 1 if function, 0 if not.
 */
int is_function(const char* str, int* len) {
    int flag = 0;
    for (int i = 0; i < (int)FUNCTION_COUNT; i++) {
        if (!strncmp(str, functions[i].name,
                     functions[i].len)) {  // сравнивает первые n символы первой стоки с n символов второй
            *len = functions[i].len;
            flag = 1;
        }
    }
    return flag;
}

/**
 * Checks if given string is an operator.
 * @param str String to check.
 * @return 1 if operator, 0 if not.
 */
int is_operator_lex(const char* str) {
    int flag = 0;
    for (int i = 0; i < (int)OPERATOR_COUNT; i++) {
        if (*str == *operations[i].symbol) flag = 1;
    }
    return flag;
}

/**
 * Finds the priority of the given operator.
 * @param op Operator to find the priority for.
 * @return The priority of the operator, or -1 if not found.
 */
int get_operator_priority(char op) {
    int prioroty = -1;
    for (int i = 0; i < (int)OPERATOR_COUNT; i++) {
        if (op == *operations[i].symbol) prioroty = operations[i].priority;
    }
    return prioroty;
}

/**
 * Processes a number in the expression.
 * @param expression The expression to process.
 * @param i Pointer to the current position in the expression.
 * @param output The output array to store the tokens in.
 * @param out_count Pointer to the current size of the output array.
 */
void process_number(const char* expression, int* i, char output[][MAX_TOKENS], int* out_count) {
    int j = 0;
    while (is_digit(expression[*i])) {
        output[*out_count][j++] = expression[(*i)++];
        printf("FIRST");
        puts(*output);
        output[*out_count][j] = '\0';
        printf("SECOND");
        puts(*output);
    }
    printf("THIRD");
    puts(*output);
    (*out_count)++;
   
}

/**
 * Processes an alphabetical character in the expression, checking if it's a function or a variable.
 * If it's a function, it's pushed onto the operator stack; if it's a variable, it's stored in output.
 * @param expression The input expression string.
 * @param i Pointer to the current position in the expression.
 * @param output The output array to store processed tokens.
 * @param out_count Pointer to the current count of tokens in the output array.
 * @param op_stack The stack to hold operators/functions.
 */
void process_alpha(const char* expression, int* i, char output[][MAX_TOKENS], int* out_count,
                   stack* op_stack) {
    int func_len = 0;
    if (is_function(&expression[*i], &func_len)) {
        // Добавляем функцию в стек
        char func[MAX_TOKENS];
        strncpy(func, &expression[*i], func_len);
        func[func_len] = '\0';
        push_lex(op_stack, func);
        *i += func_len;
    } else {
        // Добавляем переменную в выходной массив
        output[*out_count][0] = expression[(*i)++];
        output[*out_count][1] = '\0';
        (*out_count)++;
    }
}

/**
 * Processes an operator in the expression.
 * Pop operators from the stack to output based on their priority until the top of the stack has a lower
 * priority.
 * @param expression The input expression string.
 * @param i Pointer to the current position in the expression.
 * @param output The output array to store processed tokens.
 * @param out_count Pointer to the current count of tokens in the output array.
 * @param op_stack The stack to hold operators.
 * #define RESET "\033[0m"
 *#define RED "\033[31m"
 *#define GREEN "\033[32m"
 */
void process_operator(const char* expression, int* i, char output[][MAX_TOKENS], int* out_count,
                      stack* op_stack) {
    char top_op[MAX_TOKENS];
    while (!is_empty_lex(op_stack) &&
           get_operator_priority(peek(op_stack)[0]) >= get_operator_priority(expression[*i])) { // возвращается строка берем первый символ 
        printf("\033[32m" "666 %d %s \n" "\033[0m", peek(op_stack)[1], peek(op_stack));
        pop_lex(op_stack, top_op);
        strcpy(output[*out_count], top_op);  // нет вероятности переполнения буфера строки (кладем только 2 символа гарантировано)
        (*out_count)++;
    }
    char op[2] = {expression[*i], '\0'};
    push_lex(op_stack, op);
    (*i)++;
}

/**
 * Processes a closing parenthesis by popping operators from the stack to output until an opening parenthesis
 * is found.
 * @param output The output array to store processed tokens.
 * @param out_count Pointer to the current count of tokens in the output array.
 * @param op_stack The stack to hold operators.
 */
void process_closing_parenthesis(char output[][MAX_TOKENS], int* out_count, stack* op_stack) {
    char top_op[MAX_TOKENS];
    while (peek(op_stack) && strcmp(peek(op_stack), "(")) {
        pop_lex(op_stack, top_op);
        strcpy(output[*out_count], top_op);
        (*out_count)++;
    }
    if (!is_empty_lex(op_stack)) pop_lex(op_stack, top_op);  // Удаляем открывающую скобку
}

/**
 * Implements the Shunting Yard algorithm to convert infix expressions to postfix notation.
 * Processes the input expression character by character.
 * @param expression The input expression string.
 * @param output The output array to store the postfix notation.
 * @param out_count Pointer to the current count of tokens in the output array.
 */
void shunting_yard(const char* expression, char output[][MAX_TOKENS], int* out_count) {
    stack* op_stack = init_stack();
    int i = 0;

    while (expression[i] != '\0') {
        if (is_digit(expression[i])) {
            process_number(expression, &i, output, out_count);
        } else if (is_alpha(expression[i])) {
            process_alpha(expression, &i, output, out_count, op_stack);
        } else if (expression[i] == '(') {
            push_lex(op_stack, "(");
            i++;
        } else if (expression[i] == ')') {
            process_closing_parenthesis(output, out_count, op_stack);
            i++;
        } else if (is_operator_lex(&expression[i])) {
            process_operator(expression, &i, output, out_count, op_stack);
        } else {
            // Пропуск незначащих символов (например, пробелов)
            i++;
        }
    }
    // printf("42");

    // Выталкиваем оставшиеся операторы из стека
    char top_op[MAX_TOKENS];
    while (!is_empty_lex(op_stack)) {
        pop_lex(op_stack, top_op);
        strcpy(output[*out_count], top_op);
        (*out_count)++;
    }

    destroy_stack(op_stack);
}

void read_expression_from_input(char* expression) {
    printf("Введите выражение: ");
    scanf("%99[^\n]", expression);
}
