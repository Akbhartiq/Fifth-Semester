%{

//    Let's define the macros
    #define ADD 1
    #define NUM 2
    #define MUL 3
    #define LP 4
    #define RP 5

%}


space [ \t\n]
spaces {space}+
digit [0-9]
digits {digit}+


%% 

{spaces} {}
{digits} {return (NUM);}
"+" {return (ADD);}
"*" {return MUL;}
"(" {return LP;}
")" {return RP;}

%%

int yywrap()
{
    return 1;
}
