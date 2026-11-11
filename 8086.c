#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void main()
{
    int n;
    char codes[10][30],code[20];
    printf("\n Enter the number of codes:\n");
    scanf("%d",&n);

    for(int i=0;i<n;i++)
    {
        scanf("%s",codes[i]);
    }

    printf("\n target code generation");
    printf("\n************************\n");

    for(int i=0;i<n;i++)
    {
        strcpy(code,codes[i]);
        if (code[3] == '\0') {
            printf("MOV AX, %c\n", code[2]);
            printf("MOV %c, AX\n", code[0]);
            continue;

        printf("MOV AX, %c\n",code[2]);

        switch (code[3]) {
            case '+': 
                printf("ADD AX, %c\n",code[4]); 
                break;
            case '-': 
                printf("SUB AX, %c\n",code[4]);
                break;
            case '*': 
                printf("MUL AX,%c\n",code[4]); 
                break;
            case '/': 
                printf("DIV AX, %c\n",code[4]); 
                break;
            default:
                printf("; Unknown operator\n");
        }
        printf("MOV %c, AX\n",code[0]);
    }


}