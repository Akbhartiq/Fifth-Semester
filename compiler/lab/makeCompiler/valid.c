#include <stdio.h>
#include "lex.yy.c"

typedef struct node
{
    char *name;
    struct node *next;
} node;

typedef node *symbolTable;

symbolTable add(symbolTable T, char *id)
{
    symbolTable temp = T;
    while (temp)
    {
        if (!strcmp(temp->name, id))
        {
            printf("Identifier : %s is already present\n", id);
            exit(0);
        }
        temp = temp->next;
    }
    // else add the identifier
    temp = (symbolTable)malloc(sizeof(node));
    temp->name = (char *)malloc(sizeof(strlen(id) + 1));
    strcpy(temp->name, id);
    printf("Identifier: %s is added to table\n", id);
    temp->next = T;
    T = temp;
    return T;
}

int main()
{
    int token;
    symbolTable T = NULL;
    while ((token = yylex()))
    {
        // printf("Token obtained is %d\n", token);
        // printf("Token value is %s\n", yytext);
        token = -1;
        switch (token)
        {
        case ID:
            T = add(T, yytext);
            break;
        case ASG:
            printf("Assignment\n");
            break;
        case EQ:
            printf("Equal\n");
            break;
        case NE:
            printf("Not equal\n");
            break;
        case MUL:
            printf("MUltiplication\n");
            break;
        case DIV:
            printf("Division\n");
            break;
        case MOD:
            printf("Modulo Op\n");
            break;
        case LP:
            printf("Left Parenthesis\n");
            break;
        case RP:
            printf("Right Parenthesis\n");
            break;
        case ADD:
            printf("Addition\n");
            break;
        case SUB:
            printf("Subtraction\n");
            break;
        default:
            break;
        }
    }
    return 0;
}