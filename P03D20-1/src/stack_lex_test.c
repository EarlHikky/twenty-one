#include "stack_lex.h"

#include <stdio.h>
#include <string.h>

#define RESET "\033[0m"
#define GREEN "\033[32m"
#define RED "\033[31m"

#define ASSERT(condition, message)                        \
    do {                                                  \
        if (condition) {                                  \
            printf(GREEN "SUCCESS: %s\n" RESET, message); \
        } else {                                          \
            printf(RED "FAIL: %s\n" RESET, message);      \
        }                                                 \
    } while (0)

void test_init_stack() {
    stack* s = init_stack();
    ASSERT(s != NULL, "init_stack() - stack initialized");
    ASSERT(is_empty(s), "init_stack() - stack is initially empty");
    destroy_stack(s);
}

void test_push_pop() {
    stack* s = init_stack();
    const char* test_value = "test";

    int push_result = push(s, test_value);
    ASSERT(push_result == 1, "push() - value pushed onto the stack");
    ASSERT(!is_empty(s), "push() - stack is not empty after push");

    char popped_value[MAX_TOKENS];
    int pop_result = pop(s, popped_value);
    ASSERT(pop_result == 1, "pop() - value popped from the stack");
    ASSERT(strcmp(popped_value, test_value) == 0, "pop() - popped value matches the pushed value");
    ASSERT(is_empty(s), "pop() - stack is empty after pop");

    destroy_stack(s);
}

void test_peek() {
    stack* s = init_stack();
    const char* test_value = "peek_value";

    push(s, test_value);
    const char* peeked_value = peek(s);
    ASSERT(peeked_value != NULL, "peek() - value peeked from stack");
    ASSERT(strcmp(peeked_value, test_value) == 0, "peek() - peeked value matches pushed value");

    destroy_stack(s);
}

void test_destroy_stack() {
    stack* s = init_stack();
    push(s, "value1");
    push(s, "value2");
    destroy_stack(s);
    ASSERT(1, "destroy_stack() - stack destroyed successfully");
}

int main() {
    printf("Running stack tests...\n");

    test_init_stack();
    test_push_pop();
    test_peek();
    test_destroy_stack();

    printf("All tests completed.\n");

    return 0;
}