%{
    #define KEYWORDS 1
    #define IDENTIFIER 2
    #define INTEGER_CONST 3
    #define FLOAT_CONST 4
    #define ENUM_CONST 5
    #define CHAR_CONST 6
    #define STRING_LITERAL 7
    #define PUNCTUATOR 8
    #define MULTI_COM 9
    #define SINGLE_COM 10
%}


space [ \t\n]
spaces {space}+

/*Keyword defination*/
keyword             auto|enum|restrict|unsigned|break|extern|return|void|case|float|short|volatile|char|for|signed|while|const|goto|sizeof|_Bool|continue|if|static|_Complex|default|inline|struct|_Imaginary|do|int|switch|double|long|typedef|else|register|union

identifier_nondigit [a-zA-Z_]
digit               [0-9]
identifier          {identifier_nondigit}({digit}|{identifier_nondigit})*
punctuator          "["|"]"|"("|")"|"{"|"}"|"."|"->"|"++"|"--"|"&"|"*"|"+"|"-"|"~"|"!"|"/"|"%"|"<"|"<<"|">"|">>"|"<="|">="|"=="|"!="|"^"|"|"|"&&"|"||"|"?"|":"|";"|"..."|"="|"*="|"/="|"%="|"+="|"-="|"<<="|">>="|"&="|"^="|"|="|","|"#"


nonzero_dig [1-9]
integer_const {nonzero_dig}{digit}+

sign [+-]
digit_seq {digit}+
exponent_part [eE]{sign}?{digit_seq}
fractional_const ({digit_seq}?\.{digit_seq})|({digit_seq}\.)
floating_const ({fractional_const}{exponent_part}?)|({digit_seq}{exponent_part})

escape_seq \\['"?\\abfnrtv]
c_char [^\n'\\]
c_char_seq {c_char}+
char_const \'{c_char_seq}\'


enumeration_const {identifier}


s_char [^"\n\\]|{escape_seq}
s_char_seq {s_char}+
string_literal \"{s_char_seq}?\"

multi_line_com \/\*([^*]|\*[^/])*\*\/
signle_line_com \/\/[^\n]*\n



%% 
{spaces} {}


{keyword} {return KEYWORDS;}


{identifier} {return IDENTIFIER;}


{integer_const} {return INTEGER_CONST;}


{floating_const} {return FLOAT_CONST;}


{char_const} {return CHAR_CONST;}


{string_literal} {return STRING_LITERAL;}


{punctuator} {return PUNCTUATOR;}


{multi_line_com} {return MULTI_COM;}


{signle_line_com} {return SINGLE_COM;}

. {}
%%

int yywrap()
{
    return 1;
}