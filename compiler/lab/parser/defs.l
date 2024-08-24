%{
    //   Macros
       #define LP 1
       #define RP 2
       #define ADD 3
       #define SUB 4
       #define MUL 5
       #define DIV 6
       #define MOD 7
       #define ID 8
       #define NUM 9
       #define OTH 10
       #define SP 11

%}


space [ \t\n]
spaces {space}+
digit [0-9]
num [+-]?{digit}+
id [_a-zA-Z][_a-zA-Z0-9]*


%%  

{spaces} {return (SP);}
"("   {return (LP);}
")"    {return (RP);}
{id}   {return (ID);}
{num}  {return (NUM);}
"+"   {return (ADD);}
"-"  {return (SUB);}
"*"  {return (MUL);}
"/"  {return (DIV);}
"%"  {return (MOD);}
. {return (OTH);}

%%

int yywrap()
{
    return 1;
}