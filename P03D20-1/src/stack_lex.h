#ifndef STACK_LEX_H
#define STACK_LEX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lex.h"

typedef struct stack_node {
    char value[MAX_TOKENS];
    struct stack_node* next;
} stack_node;

typedef struct stack {
    stack_node* top;
} stack;

stack* init_stack();
int is_empty_lex(stack* s);
int push_lex(stack* s, const char* value);
int pop_lex(stack* s, char* value);
void destroy_stack(stack* s);
char* peek(stack* s);

#endif