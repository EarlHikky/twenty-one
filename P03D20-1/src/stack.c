#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stack_node {
    double value;
    struct stack_node* next;
};

struct stack {
    struct stack_node* top;
};

struct stack* init();
int push(struct stack* s, double value);
double pop(struct stack* s);
void destroy(struct stack* s);
int is_empty(struct stack* s);

struct stack* init() {
    struct stack* s = (struct stack*)malloc(sizeof(struct stack));
    if (s) {
        s->top = NULL;
    }
    return s;
}

int push(struct stack* s, double value) {
    struct stack_node* new_node = (struct stack_node*)malloc(sizeof(struct stack_node));
    if (!new_node) return 0;

    new_node->value = value;
    new_node->next = s->top;
    s->top = new_node;
    return 1;
}

double pop(struct stack* s) {
    if (is_empty(s)) {
        return -1;
    }

    struct stack_node* temp = s->top;
    double popped_value = temp->value;
    s->top = temp->next;
    free(temp);
    return popped_value;
}

int is_empty(struct stack* s) { return s->top == NULL; }

void destroy(struct stack* s) {
    while (!is_empty(s)) {
        pop(s);
    }
    free(s);
}
