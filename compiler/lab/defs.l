%{
      
       #define ASG 1
       #define ID 2
       #define NUM 3
       #define LP 4
       #define RP 5
       #define IF 6
       #define ELSE 7
       #define EQ 8
       #define NE 9
       #define GT 10
       #define LT 11
       #define GE 12
       #define LE 13

%}


space [ \t\n]
spaces {space}+
digit [0-9]
digits {digit}+
frac \.{digits}
expt [Ee][+-]?{digits}
number {digits}{frac}?{expt}?
id [_a-zA-Z][_a-zA-Z0-9]*


%%
{spaces} {}
{number} {return (NUM);}
"if"     {return (IF);}
"else"   {return (ELSE);}
{id}     {return (ID);}
"="      {return (EQ);}
":="     {return (ASG);}
">="     {return (GE);}
">"      {return (GT);}
"<="     {return (LT);}
"<>"     {return (NE);}
"<"      {return (LT);}
"("      {return (LP);}
")"      {return (RP);}
%%

int yywrap(){
    return 1;
}