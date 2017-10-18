%{
#include <stdio.h>
extern int yylex();
extern int yyparse();
extern FILE * yyin;

void yyerror(const char * s);
%}

/* add enum or type for executing commands/flags */
%union {
  int ival;
char * sval;
}

%token CD
%token <sval> STRING

%%

parse:
CD STRING {printf("cd into %s dir\n", $2);}

%%

int main(int argc, char * argv[])
{
do {
yyparse();
} while (!feof(stdin));
}

void yyerror(const char * s) {
// TODO: actually implement this
printf("Parsing error!\n");
}
