#include <stdio.h>
#include <stdlib.h>
#include "lex.yy.c"

int main()
{
    int nextToken;
    int count = 0;
    while ((nextToken = yylex()))
    {
        // printf("Token is : {%s}\n", yytext);
        switch (nextToken)
        {
        case ZERO:
            printf("zero ");
            break;
        case ONE:
            printf("one ");
            break;
        case TWO:
            printf("two ");
            break;
        case THREE:
            printf("three ");
            break;
        case FOUR:
            printf("four ");
            break;
        case FIVE:
            printf("five ");
            break;
        case SIX:
            printf("six ");
            break;
        case EIGHT:
            printf("eight ");
            break;
        case NINE:
            printf("nine ");
            break;
        default:
            printf("\n");
            break;
        }
    }
    printf("\n");
}