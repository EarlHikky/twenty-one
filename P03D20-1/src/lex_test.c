#include "lex.h"

#include <stdio.h>
#include <string.h>

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"

void print_polish_notation(char output[][MAX_TOKENS], int count) {
    for (int i = 0; i < count; i++) {
        printf("%s ", output[i]);
    }
    printf("\n");
}

void print_polish_notation_test() {
    char output[MAX_TOKENS][MAX_TOKENS];
    int out_count = 0;

    const char *expressions[] = {
        "x*x",
        "x",
        "sin(x)",
        "x*x*x",
        "x+x*x",
        "1/x",
        "tan(x)",
        "x*sin(x)",
        "sin(sin(sin(sin(1/ln(x*x)))))",
        "1.0",
        "-1",
        "-123+666",
        "-x*2",
        "sqrt(-(1/(-x*x)))",
    };

    // https://www.semestr.online/informatics/polish.php
    const char *expected_outputs[] = {
        "x x *",
        "x",
        "x sin",
        "x x * x *",
        "x x x * +",
        "1 x /",
        "x tan",
        "x x sin *",
        "1 x x * ln / sin sin sin sin",
        "1.0",
        "1 -",
        "123 - 666 +",
        "x 2 * -",
        "1 x x * - / - sqrt",
    };

    int num_expressions = sizeof(expressions) / sizeof(expressions[0]);

    for (int i = 0; i < num_expressions; i++) {
        out_count = 0;
        shunting_yard(expressions[i], output, &out_count);

        printf("Reverse Polish Notation: ");
        print_polish_notation(output, out_count);

        char result[MAX_TOKENS * MAX_TOKENS] = "";
        for (int j = 0; j < out_count; j++) {
            strcat(result, output[j]);
            if (j < out_count - 1) {
                strcat(result, " ");
            }
        }

        if (strcmp(result, expected_outputs[i]) == 0) {
            printf(GREEN "Test %d passed.\n" RESET, i + 1);
        } else {
            printf(RED "Test %d failed: expected '%s', got '%s'.\n" RESET, i + 1, expected_outputs[i],
                   result);
        }
    }
}

void read_expression_from_input_test() {
    char expression[MAX_TOKENS];
    char output[MAX_TOKENS][MAX_TOKENS];
    int out_count = 0;

    read_expression_from_input(expression);

    shunting_yard(expression, output, &out_count);

    print_polish_notation(output, out_count);
}

int main() {
#ifdef TEST_INPUT
    read_expression_from_input_test();
#else
    print_polish_notation_test();
#endif
    return 0;
}
