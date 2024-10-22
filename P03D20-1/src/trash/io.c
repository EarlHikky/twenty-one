#include <stdio.h>
#include <string.h>

#define MAX_TOKENS 100

void read_expression_from_input(char output[MAX_TOKENS][MAX_TOKENS], int* out_count) {
    char expression[MAX_TOKENS];

    // Ввод выражения с помощью простого scanf
    printf("Введите математическое выражение: ");
    scanf("%s", expression);  // Считываем строку до первого пробела

    // Инициализация считывания строки
    *out_count = 0; // Сбрасываем количество токенов

    // Считываем токены по одному, здесь один токен - это целая строка
    strcpy(output[*out_count], expression);
    (*out_count)++;
    printf("%d", *out_count);
}

int main() {
    char output[MAX_TOKENS][MAX_TOKENS];
    int out_count = 0;

    // Считывание выражения с клавиатуры
    read_expression_from_input(output, &out_count);

    // Вывод считанного выражения
    printf("Выражение считано: ");
    for (int i = 0; i < out_count; i++) {
        printf("%s ", output[i]);
    }
    printf("\n");

    return 0;
}