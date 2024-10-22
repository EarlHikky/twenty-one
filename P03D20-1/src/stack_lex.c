#include "stack_lex.h"

/**
 * Creates a new empty stack.
 *
 * @return A newly allocated stack, or NULL if there was a memory allocation error.
 */
stack* init_stack() {
    stack* s = (stack*)malloc(sizeof(stack));
    if (s) {
        s->top = NULL;
    }
    return s;
}

int is_empty_lex(stack* s) { return s->top == NULL; }

/**
 * Pushes a new value onto the stack.
 *
 * @param s The stack to push the value onto.
 * @param value The value to push onto the stack.
 *
 * @return 1 if the value was successfully pushed, 0 if there was a memory allocation error.
 */
int push_lex(stack* s, const char* value) {
    stack_node* new_node = (stack_node*)malloc(sizeof(stack_node));
    if (!new_node) return 0;

    strncpy(new_node->value, value, MAX_TOKENS);
    new_node->next = s->top;
    s->top = new_node;
    return 1;
}

/**
 * Removes the top element from the stack and copies its value into the provided buffer.
 *
 * @param s The stack from which to pop the value.
 * @param value A buffer to store the popped value. It should be large enough to hold a value of MAX_TOKENS.
 *
 * @return 1 if the value was successfully popped, 0 if the stack was empty.
 */
int pop_lex(stack* s, char* value) {
    if (is_empty_lex(s)) {
        return 0;
    }

    stack_node* temp = s->top;
    strncpy(value, temp->value, MAX_TOKENS);
    s->top = temp->next;
    free(temp);
    return 1;
}

/**
 * Frees all memory associated with a stack, including the stack struct itself.
 *
 * @param s The stack to destroy.
 */
void destroy_stack(stack* s) {
    while (!is_empty_lex(s)) {
        stack_node* temp = s->top;
        s->top = temp->next;
        free(temp);
    }
    free(s);
}

/**
 * Returns the top element from the stack without removing it.
 *
 * @param s The stack from which to peek the value.
 *
 * @return The top element of the stack, or NULL if the stack is empty.
 */
char* peek(stack* s) {
    if (is_empty_lex(s)) {
        return NULL;
    }
    return s->top->value;
}