%{
#include "parse.tab.h"
#define YY_DECL extern int yylex()
%}

/* string needs to include file characters */

%%
cd {return CD;}
[a-zA-Z0-9]+ {yylval.sval = strdup(yytext); return STRING;}
%%
