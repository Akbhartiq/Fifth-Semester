%{
    #include "ytab.h"  /*created when yacc file is given to yacc tool*/
    #include<stdio.h>
    int yylval;        /*Passed between yacc and lex*/
%}

%%
"int"[ ]+ {return KEY;}
"float"[ ]+ {return KEY;}
"char"[ ]+ {return KEY;}
"double"[ ]+ {return KEY;}
"short"[ ]+ {return KEY;}
"long int"[ ]+ {return KEY;}
[_a-ZA-Z][_a-zA-Z0-9]* {return ID;}
[0-9]+ {return NUM;}
[/t];
[;] {return COLON;}
\n {return 0;}
.   {return yytext[0];}
%%

/*yywrap thing*/

int yywrap()
{
    return 1;
}
