#include <stdio.h>
#include <string.h>

int main(void) {
    int n;
    char op, arg1[20], arg2[20], result[20];

    printf("Enter number of three address instructions: ");
    scanf("%d", &n);

    printf("\nEnter TAC (Example: a = b + c)\n");

    for (int i = 0; i < n; i++) {
        scanf("%19s = %19s %c %19s", result, arg1, &op, arg2);

        printf("\n8086 Assembly Code:\n");
        printf("----------------------\n");
        printf("MOV AX, %s\n", arg1);

        switch (op) {
            case '+': 
                printf("ADD AX, %s\n", arg2); 
                break;
            case '-': 
                printf("SUB AX, %s\n", arg2); 
                break;
            case '*': 
                printf("MUL %s\n", arg2); 
                break;
            case '/': 
                printf("DIV %s\n", arg2); 
                break;
            default:
                printf("; Unknown operator\n");
        }
        printf("MOV %s, AX\n", result);
    }

    return 0;
}