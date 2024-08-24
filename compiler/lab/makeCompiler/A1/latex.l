%{
    /*Macros*/
    #define TD 1    //tilda
    #define BK 2    //alphabetic command
    #define BCM 3   //single char command
    #define CM 4    //comment
    #define ENV 5   //envrionment variable
    #define MT1 6   //inline math equations
    #define MT2 7   //display math equations
    #define MT3 8   //display math equations
%}

/*Define the pattern*/
tilda [~]
env \\[b][e][g][i][n]\{[^\}]*\}
back \\[a-zA-Z]+
math2 \\\[
backCom \\.
comment [%].*
math3 [$][$]
math1 [$]
skip \\\]
end \\[e][n][d]


%% 
{end} {}
{skip} {return MT2;}
{comment} {return CM;}
{tilda} {return TD;}
{math3} {return MT3;}
{math1} {return MT1;}
{math2} {return MT2;}
{env} {return ENV;}
{back} {return BK;}
{backCom} {return BCM;}
. {}
"\n" {}
%%

int yywrap()
{ return 1;
}