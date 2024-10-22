#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Node {
    char data[10];  // Может быть оператором или числом
    struct Node* left;
    struct Node* right;
} Node;

// Функция для создания нового узла
Node* create_node(const char* data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    strcpy(new_node->data, data);
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// Проверка, является ли символ оператором
int is_operator(char ch) {
    return (ch == '+' || ch == '*' || ch == '/');
}

// Приоритет операций
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Преобразование строки в польскую нотацию с использованием стека
void to_postfix(const char* infix, char* postfix) {
    char stack[100];
    int top = -1;
    int k = 0;

    for (int i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];

        // Если символ - операнд, добавляем его к результату
        if ((ch >= '0' && ch <= '9') || ch == '.') {
            postfix[k++] = ch;
        } else if (is_operator(ch)) {
            postfix[k++] = ' ';
            // Удаляем операторы с большим или равным приоритетом из стека
            while (top != -1 && precedence(stack[top]) >= precedence(ch)) {
                postfix[k++] = stack[top--];
                postfix[k++] = ' ';
            }
            stack[++top] = ch;
        } else if (ch == '(') {
            stack[++top] = ch;
        } else if (ch == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[k++] = stack[top--];
                postfix[k++] = ' ';
            }
            top--;  // Убираем '(' из стека
        }
    }

    // Добавляем оставшиеся операторы из стека
    while (top != -1) {
        postfix[k++] = ' ';
        postfix[k++] = stack[top--];
    }
    postfix[k] = '\0';
}

// Построение бинарного дерева из постфиксной нотации
Node* build_tree(char* postfix) {
    Node* stack[100];
    int top = -1;
    char* token = strtok(postfix, " ");

    while (token != NULL) {
        if (is_operator(token[0]) && strlen(token) == 1) {
            // Оператор: создаем узел с операцией и двумя операндами
            Node* op_node = create_node(token);
            op_node->right = stack[top--];  // Второй операнд
            op_node->left = stack[top--];   // Первый операнд
            stack[++top] = op_node;         // Помещаем узел обратно в стек
        } else {
            // Операнд: создаем узел и помещаем в стек
            stack[++top] = create_node(token);
        }
        token = strtok(NULL, " ");
    }

    return stack[top];  // Корень дерева
}

// Прямой обход дерева (инфиксная запись)
void print_infix(Node* root) {
    if (root != NULL) {
        if (is_operator(root->data[0])) printf("(");
        print_infix(root->left);
        printf("%s", root->data);
        print_infix(root->right);
        if (is_operator(root->data[0])) printf(")");
    }
}

// Освобождение памяти дерева
void free_tree(Node* root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

int main() {
    char infix[100], postfix[100];
    
    printf("Введите выражение: ");
    fgets(infix, sizeof(infix), stdin);
    infix[strcspn(infix, "\n")] = '\0';  // Удаление символа новой строки

    to_postfix(infix, postfix);
    printf("Постфиксная запись: %s\n", postfix);

    Node* root = build_tree(postfix);

    printf("Инфиксная запись из дерева: ");
    print_infix(root);
    printf("\n");

    free_tree(root);
    return 0;
}