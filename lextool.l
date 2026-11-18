%{
#include <stdio.h>
#include <stdlib.h>
%}

%%
[0-9]+ {
    printf("%s : NUMBER\n", yytext);
}

[a-zA-Z_][a-zA-Z0-9_]* {
    printf("%s : IDENTIFIER\n", yytext);
}

"+"|"-"|"*"|"/"|"=" {
    printf("%s : OPERATOR\n", yytext);
}

"("|")"|"{"|"}"|";"|"," {
    printf("%s : DELIMITER\n", yytext);
}

[ \t\n]+ ;

. {
    printf("%s : INVALID TOKEN\n", yytext);
}
%%

int main()
{
    printf("Enter a program "
           "(Press Ctrl+D in Linux/Mac or Ctrl+Z "
           "then Enter in Windows to finish):\n");

    yylex();

    return 0;
}

int yywrap()
{
    return 1;
}
