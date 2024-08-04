/*This program is written the count the number of words in file*/
%{
    #define WD 1
%}

/*Declare the patters here*/

word [a-zA-Z]+

%% 
{word}  {return(WD);}
. {return -1;}
%%

int yywrap()
{ return 1;}


