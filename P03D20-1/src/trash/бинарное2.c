#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

Node* createNode(char value);
Node* buildTree(const char* postfix);
int precedence(char op);
Stack* createStack(int maxSize);
int isEmpty(Stack* stack);
void push(Stack* stack, char item);
char pop(Stack* stack);
char peek(Stack* stack);
void infixToPostfix(const char* infix, char* postfix);

// Структура стека
typedef struct Stack {
    char* items;
    int top;
    int maxSize;
} Stack;

// Структура узла бинарного дерева
typedef struct Node {
    char value; // Хранит оператор или операнд
    struct Node* left; // Указатель на левого потомка
    struct Node* right; // Указатель на правого потомка
} Node;

Node* createNode(char value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* buildTree(const char* postfix) {
    Stack* stack = createStack(strlen(postfix));
    Node* temp;

    for (int i = 0; i < strlen(postfix); i++) {
        char token = postfix[i];

        if (isalnum(token)) { // Если токен — операнд, создаем новый узел и помещаем в стек
            temp = createNode(token);
            push(stack, (int)temp); // Примечание: для удобства храним указатели как int
        } else { // Если токен — оператор, создаем узел и устанавливаем левого и правого потомка
            Node* node = createNode(token);
            node->right = (Node*)pop(stack);
            node->left = (Node*)pop(stack);
            push(stack, (int)node);
        }
    }

    // Верхний элемент стека — корень дерева
    return (Node*)pop(stack);
}

int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}


// Функция для создания стека
Stack* createStack(int maxSize) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->maxSize = maxSize;
    stack->top = -1;
    stack->items = (char*)malloc(sizeof(char) * maxSize);
    return stack;
}

// Функция для проверки, пуст ли стек
int isEmpty(Stack* stack) {
    return stack->top == -1;
}

// Функция для добавления элемента в стек
void push(Stack* stack, char item) {
    stack->items[++stack->top] = item;
}

// Функция для удаления элемента из стека
char pop(Stack* stack) {
    return stack->items[stack->top--];
}

// Функция для получения верхнего элемента стека
char peek(Stack* stack) {
    return stack->items[stack->top];
}

// Функция для преобразования инфиксного выражения в постфиксное
void infixToPostfix(const char* infix, char* postfix) {
    Stack* stack = createStack(strlen(infix));
    int k = 0;

    for (int i = 0; i < strlen(infix); i++) {
        char token = infix[i];

        if (isalnum(token)) { // Если токен — операнд, добавляем его в постфиксное выражение
            postfix[k++] = token;
        } else if (token == '(') { // Если токен — '(', помещаем его в стек
            push(stack, token);
        } else if (token == ')') { // Если токен — ')', извлекаем из стека до '('
            while (!isEmpty(stack) && peek(stack) != '(') {
                postfix[k++] = pop(stack);
            }
            pop(stack); // Убираем '('
        } else { // Если токен — оператор
            while (!isEmpty(stack) && precedence(peek(stack)) >= precedence(token)) {
                postfix[k++] = pop(stack);
            }
            push(stack, token);
        }
    }

    // Извлекаем оставшиеся элементы из стека
    while (!isEmpty(stack)) {
        postfix[k++] = pop(stack);
    }

    postfix[k] = '\0'; // Завершаем строку
    free(stack->items);
    free(stack);
}


int main() {
    const char* infix = "a+(b-c)*d";
    char postfix[100];

    infixToPostfix(infix, postfix);
    printf("Postfix Expression: %s\n", postfix);

    Node* root = buildTree(postfix);
    
    // Здесь можно добавить функции для обхода дерева и его отображения

    return 0;
}