%{
    /*Define the macros*/
    #define ID 1
    #define ASG 2
    #define EQ 3
    #define NE 4
    #define ADD 5
    #define SUB 6
    #define MUL 7
    #define DIV 8
    #define LP 9
    #define RP 10
    #define MOD 11
%}

/*Pattern Declaration*/


/*Rule for actions*/
%% 

%%

int yywrap(){
    return 1;
}
