%{
#include <stdio.h>
extern void yyerror(char* s);
extern int yylex();
extern int readInputForLexer(char* buffer,int *numBytesRead,int maxBytesToRead);
%}

%token FUNCTION_PLUS FUNCTION_MINUS NUMBER

%%

expression:
    NUMBER FUNCTION_PLUS NUMBER { printf("got expression!  Yay!\n"); }
    ;

%%
