%{
    #define ZERO 0
    #define ONE 1
    #define TWO 2
    #define THREE 3
    #define FOUR 4
    #define FIVE 5
    #define SIX 6
    #define SEVEN 7
    #define EIGHT 8
    #define NINE 9
%}

%%
"0" {return(ZERO);}
"1" {return ONE;}
"2" {return TWO;}
"3" {return THREE;}
"4" {return FOUR;}
"5" {return FIVE;}
"6" {return SIX;}
"7" {return SEVEN;}
"8" {return EIGHT;}
"9" {return NINE;}
.   {return -1;}
%%

int yywrap()
{
    return 1;
}