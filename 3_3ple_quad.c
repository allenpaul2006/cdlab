#include <stdio.h>
#include <ctype.h>
#include <string.h>

char stack[100];
int top = -1;
char postfix[100];
int p = 0;

void push(char c) {
    stack[++top] = c;
}

char pop() {
    return stack[top--];
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

void infixtopostfix(char infix[]) {
    int i;
    char symbol;
    for (i = 0; infix[i] != '\0'; i++) {
        symbol = infix[i];
        if (isalnum(symbol)) 
        {
            postfix[p++] = symbol;
        }
        else if (symbol == '(') 
        {
            push(symbol);
        }
        else if (symbol == ')') 
        {
            while (top != -1 && stack[top] != '(') 
            {
                postfix[p++] = pop();
            }
            if (top != -1) pop();
        }
        else 
        {
            while (top != -1 && stack[top] != '(' && precedence(stack[top]) >= precedence(symbol)) 
            {
                postfix[p++] = pop();
            }
            push(symbol);
        }
    }
    while (top != -1) {
        postfix[p++] = pop();
    }
    postfix[p] = '\0';
}

/* Experiment 9: Three Address Code Generation */
void generateTAC() {
    char operandstack[100][20];
    int operandtop = -1;
    int tempcount = 1;

    for (int i = 0; postfix[i] != '\0'; i++) {
        char symbol = postfix[i];
        if (isalnum(symbol)) {
            operandtop++;
            operandstack[operandtop][0] = symbol;
            operandstack[operandtop][1] = '\0';
        } else {
            char op1[20], op2[20], temp[20];
            strcpy(op2, operandstack[operandtop--]);
            strcpy(op1, operandstack[operandtop--]);
            sprintf(temp, "t%d", tempcount++);
            printf("%s = %s %c %s\n", temp, op1, symbol, op2);

            operandtop++;
            strcpy(operandstack[operandtop], temp);
        }
    }
}

/* Quadruple representation */
void Quadruple() {
    char operandstack[100][20];
    int operandtop = -1;
    int tempcount = 1;

    for (int i = 0; postfix[i] != '\0'; i++) {
        char symbol = postfix[i];
        if (isalnum(symbol)) {
            operandtop++;
            operandstack[operandtop][0] = symbol;
            operandstack[operandtop][1] = '\0';
        } else {
            char op1[20], op2[20], temp[20];
            strcpy(op2, operandstack[operandtop--]);
            strcpy(op1, operandstack[operandtop--]);
            sprintf(temp, "t%d", tempcount++);
            printf("%c\t%s\t%s\t%s\n", symbol, op1, op2, temp);

            operandtop++;
            strcpy(operandstack[operandtop], temp);
        }
    }
}

/* Triple representation */
void triple() {
    char operandstack[100][20];
    int operandtop = -1;
    int tempcount = 0;//change

    for (int i = 0; postfix[i] != '\0'; i++) {
        char symbol = postfix[i];
        if (isalnum(symbol)) {
            operandtop++;
            operandstack[operandtop][0] = symbol;
            operandstack[operandtop][1] = '\0';
        } else {
            char op1[20], op2[20], temp[20];
            strcpy(op2, operandstack[operandtop--]);
            strcpy(op1, operandstack[operandtop--]);
            sprintf(temp, "(%d)", tempcount++);
            printf("%c\t%s\t%s\n", symbol, op1, op2);

            
            operandtop++;
            strcpy(operandstack[operandtop], temp);
        }
    }
}

int main() {
    char infix[100];

    printf("enter an expression: ");
    scanf("%s", infix);

    infixtopostfix(infix);
    printf("\npostfix expression: %s\n", postfix);

    printf("\nthree address code:\n");
    generateTAC();

    printf("\nQUADRUPLE:\n");
    printf("op\targ1\targ2\tresult\n");
    Quadruple();

    printf("\nTRIPLE:\n");
    printf("op\targ1\targ2\n");
    triple();

    return 0;
}