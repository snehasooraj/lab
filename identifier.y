%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(char *s);
int yylex();
%}

%token ID

%%
S : ID
{
    printf("Valid Identifier\n");
}
;
%%

int main()
{
    printf("Enter the identifier: ");
    yyparse();
    return 0;
}

void yyerror(char *s)
{
    printf("Invalid Identifier\n");
}
