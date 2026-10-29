#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* This lab version accepts expressions made from operand i and binary
   operators +, -, *, /. The input must end with exactly one final $. */
int getIndex(char c) {
    switch (c) {
        case '+': case '-': return 0;
        case '*': case '/': return 1;
        case 'i': return 2;
        case '$': return 3;
        default: return -1;
    }
}

/* Validate the complete input before running the precedence-table trace.
   This prevents malformed expressions from being accepted by the old
   symbol-by-symbol reduction logic. */


int validExpression(const char *input) 
{
    int len = strlen(input);
    if (len < 2 || input[len - 1] != '$') return 0;

    /* '$' must occur only once, at the very end. */
    for (int i = 0; i  < len-1; i++)
        if (input[i] == '$') return 0;

    int expectOperand = 1;
    for (int i = 0; i  < len-1; i++) 
    {
        char c = input[i];
        if (expectOperand) 
        {
            if (c != 'i') return 0;
            expectOperand = 0;
        }
         else 
        {
            if (c != '+' && c != '-' && c != '*' && c != '/') return 0;
            expectOperand = 1;
        }
    }
    return !expectOperand;
}

int main(void) {
    /* Rows and columns: additive operators, multiplicative operators, i, $. */
    char precTable[4][4] = {
        {'>', '<', '<', '>'},
        {'>', '>', '<', '>'},
        {'>', '>', ' ', '>'},
        {'<', '<', '<', '='}
    };

    char stack[100], input[100];
    int top = 0, i = 0;
    stack[0] = '$';
    stack[1] = '\0';

    printf("Enter input string (example: i+i*i$): ");
    scanf("%s",input);

    if (!validExpression(input)) {
        printf("\nResult: Parsing Failed \n");
        return 0;
    }

    printf("\n%-15s %-15s %-10s %s\n", "Stack", "Input", "Precedence", "Action");
    printf("----------------------------------------------------------\n");

    while (1) {
        char stackTop = stack[top];
        char currentInput = input[i];
        int row = getIndex(stackTop);
        int col = getIndex(currentInput);

        if (row == -1 || col == -1) {
            printf("\nResult: Parsing Failed\n");
            return 0;
        }

        char relation = precTable[row][col];
        printf("%-15s %-15s %-10c ", stack, &input[i], relation);

        if (stackTop == '$' && currentInput == '$' && top == 0 && i == (int)strlen(input) - 1) {
            printf("ACCEPT\n\nResult: Input string is Successfully Parsed!\n");
            break;
        }

        if (relation == '<' || relation == '=') {
            if (top >= 98 || i >= (int)strlen(input) - 1) {
                printf("ERROR\n\nResult: Parsing Failed\n");
                break;
            }
            stack[++top] = currentInput;
            stack[top + 1] = '\0';
            i++;
            printf("Shift '%c'\n", currentInput);
        } else if (relation == '>') {
            if (top == 0) {
                printf("ERROR\n\nResult: Parsing Failed\n");
                break;
            }
            char popped = stack[top--];
            stack[top + 1] = '\0';
            printf("Reduce '%c'\n", popped);
        } else {
            printf("ERROR\n\nResult: Parsing Failed\n");
            break;
        }
    }
    return 0;
}