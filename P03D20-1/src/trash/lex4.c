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

Function functions[] = {
    {"ln", 2},
    {"sin", 3},
    {"cos", 3},
    {"tan", 3},
    {"ctg", 3},
    {"sqrt", 4}
};

Operation operations[] = {
    {"(", 0},
    {")", 0},
    {"*", 2},
    {"/", 2},
    {"+", 1},
    {"-", 1}
};

int is_digit(char c) {
    return (c >= '0' && c <= '9');
}

int is_alpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int is_function(const char *str, int *len) {
    int flag = 0;
    for (int i = 0; i < FUNCTION_COUNT; i++) {       
        if (!strncmp(str, functions[i].name, functions[i].len)) {  // сравнивает первые n символы первой стоки с n символов второй
            *len = functions[i].len;
            flag = 1;
        }
    }
    return flag;
}

int is_operator(const char *str) {
    int flag = 0;
    for (int i = 0; i < OPERATOR_COUNT; i++) {
        if (*str == *operations[i].symbol) {
            flag = 1;
        }
    }
    return flag;
}

int get_operator_priority(char op) {
    int prioroty = -1;
    for (int i = 0; i < OPERATOR_COUNT; i++) {
        if (op == *operations[i].symbol) {
            prioroty = operations[i].priority;
        }
    }
    return prioroty;
}

// Алгоритм сортировочной станции для обратной польской нотации
void shunting_yard(const char *expression, char output[][MAX_TOKENS], int *out_count) {
    char stack[MAX_TOKENS][MAX_TOKENS];  // Стек для операторов
    int stack_top = -1;  // Индекс вершины стека

    int i = 0;
    while (expression[i] != '\0') {
        if (is_digit(expression[i])) {
            // Если цифра, записываем в выходной массив
            int j = 0;
            while (is_digit(expression[i])) {
                output[*out_count][j++] = expression[i++];
            }
            output[*out_count][j] = '\0';
            (*out_count)++;
        } else if (is_alpha(expression[i])) {
            // Если это функция или переменная
            int func_len = 0;
            if (is_function(&expression[i], &func_len)) {
                // Если это функция, добавляем её в стек
                strncpy(stack[++stack_top], &expression[i], func_len);
                stack[stack_top][func_len] = '\0'; // Завершаем строку нулём
                i += func_len;
            } else {
                // Если переменная, добавляем её в выходной массив
                output[*out_count][0] = expression[i++];
                output[*out_count][1] = '\0';
                (*out_count)++;
            }
        } else if (expression[i] == '(') {
            // Если открывающая скобка, добавляем в стек
            strncpy(stack[++stack_top], "(", 1);
            stack[stack_top][1] = '\0';
            i++;
        } else if (expression[i] == ')') {
            // Если закрывающая скобка, выгружаем операторы из стека до открывающей скобки
            while (stack_top >= 0 && strcmp(stack[stack_top], "(") != 0) {
                strcpy(output[*out_count], stack[stack_top--]);
                (*out_count)++;
            }
            if (stack_top >= 0) stack_top--; // Удаляем открывающую скобку
            i++;
        } else if (is_operator(&expression[i])) {
            // Если оператор, выталкиваем операторы с большим или равным приоритетом из стека
            while (stack_top >= 0 && get_operator_priority(stack[stack_top][0]) >= get_operator_priority(expression[i])) {
                strcpy(output[*out_count], stack[stack_top--]);
                (*out_count)++;
            }
            // Кладём текущий оператор в стек
            strncpy(stack[++stack_top], &expression[i], 1);
            stack[stack_top][1] = '\0';
            i++;
        } else {
            i++;  // Пропуск незначащих символов (например, пробелов)
        }
    }
    // Выталкиваем оставшиеся операторы из стека
    while (stack_top >= 0) {
        strcpy(output[*out_count], stack[stack_top--]);
        (*out_count)++;
    }
}

// Функция для вывода польской нотации
void print_polish_notation(char output[][MAX_TOKENS], int count) {
    for (int i = 0; i < count; i++) {
        printf("%s ", output[i]);
    }
    printf("\n");
}

// int main() {
//     const char *expression1 = "x*x";                   // x*x
//     const char *expression2 = "x";                     // x
//     const char *expression3 = "sin(x)";                // sin(x)
//     const char *expression4 = "x*x*x";                 // x*x*x
//     const char *expression5 = "x+x*x";                 // x+x*x
//     const char *expression6 = "1/x";                   // 1/x
//     const char *expression7 = "tan(x)";                // tan(x)
//     const char *expression8 = "x*sin(x)";              // x*sin(x)
//     const char *expression9 = "sin(sin(sin(sin(1/ln(x*x)))))"; // sin(sin(sin(sin(1/ln(x*x)))))
//     const char *expression10 = "1";                     // 1
//     const char *expression11 = "-1";                    // -1
//     const char *expression12 = "-x*2";                  // -x*2
//     const char *expression13 = "sqrt(-(1/(-x*x)))";    // sqrt(-(1/(-x*x)))


    
//     char output[MAX_TOKENS][MAX_TOKENS];
//     int out_count = 0;

//     for (int i = 0; i < 14; i++) {
//         shunting_yard(expression, output, &out_count);
//          printf("Reverse Polish Notation: ");
//         print_polish_notation(output, out_count);
//     }  

//     return 0;
// }

// Функция для тестирования print_polish_notation
void test_print_polish_notation() {
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
        "1",
        "-1",
        "-x*2",
        "sqrt(-(1/(-x*x)))"
    };
    
    int num_expressions = sizeof(expressions) / sizeof(expressions[0]);

    for (int i = 0; i < num_expressions; i++) {
        out_count = 0; // Сброс счетчика перед каждым тестом
        shunting_yard(expressions[i], output, &out_count);
        
        // Проверка, что выходной массив содержит правильное значение
        assert(strcmp(output[0], expressions[i]) == 0);
        
        // Для каждого вызова print_polish_notation
        printf("Reverse Polish Notation: ");
        print_polish_notation(output, out_count);
    }
}

int main() {
    test_print_polish_notation();
    return 0;
}