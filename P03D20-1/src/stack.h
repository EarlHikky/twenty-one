#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

struct stack_node {
    double value;
    struct stack_node* next;
};

struct stack {
    struct stack_node* top;
};

struct stack* init();
double push(struct stack* s, double value);
double pop(struct stack* s);
void destroy(struct stack* s);
double is_empty(struct stack* s);

#endif
