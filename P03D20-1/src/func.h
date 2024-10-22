#ifndef FUNC_H
#define FUNC_H
#include "lex.h"
#include "stack.h"

double read_number(char *);
double read_function(char *, struct stack *, int *);
double read_PN(char arr[][MAX_TOKENS], int len, double x);
double read_opp(char *arr, struct stack *, int *);
int is_operator(char);
int is_number(char);
int is_func(char *);

int is_operator(char);
int is_number(char);
int is_func(char *);

#endif
