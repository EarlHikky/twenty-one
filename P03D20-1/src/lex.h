#ifndef LEX_H
#define LEX_H

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

void read_expression_from_input(char *expression);
void shunting_yard(const char *expression, char output[][MAX_TOKENS], int *out_count);
int get_operator_priority(char op);
int is_operator_lex(const char *str);
int is_function(const char *str, int *len);
int is_alpha(char c);
int is_digit(char c);

void print_polish_notation_test();
void print_polish_notation(char output[][MAX_TOKENS], int count);

#endif