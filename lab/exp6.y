%{
#include <stdio.h>
#include <stdlib.h>
int yylex(void);
void yyerror(char *s);
%}
%token DIGIT ALPHA

%%
var : ALPHA
| var ALPHA
| var DIGIT
;
%%
int main() {
printf("Enter a variable name: ");
yyparse();
printf("Valid Variable!\n");
return 0;
}
void yyerror(char *s) {
printf("Invalid Variable!\n");
exit(1);
}
