%{
    #include<stdio.h>
    int flag=0;
%}

%token ID KEY COLON COMMA NUM


%%
stmt: list {printf("\nDelaration is validated\n");}
;

list: KEY list
    | list ',' list
    | list ','',' {printf("Syntax Error: Consecutive Commas Used: Invalid");exit(0);}
    | list COL 
    | ID '['NUM']'
    | ID '['NUM'.'']' {printf("\nFloat Number can not be the size of of an array\n");exit(0);}
    | ID '['ID']' {printf("\nSize of an array should be Integer\n");exit(0);}
    | ID '['ID {printf("\nClosing bracket missing in Array Declartion\n");exit(0);}
    | ID '[' {printf("\nSize of array should be given\n");exit(0);}
    | ID
    ;

COL: COLON
    | COLON COL {printf("\nSyntax Error: consecutive semicolon are used: invalid");exit(0);}
    ;
%%

main()
{
    printf("Enter valid Declaration\n");
    yyparse();
}

yyerror()

{printf("Invalid Statement\n");exit(1);}