%{
#include<stdio.h>
int yylex();
int yyerror(char *s);
%}

%token NUMBER
%left '+''-'
%left '*''/'

%%
st : exp { printf("Answer=%d\n", $1); }
	;
exp : exp '+' exp { $$=$1+$3; }
	| exp '-' exp { $$ = $1 - $3; }
	| exp '*' exp { $$ = $1 * $3; }
	| exp '/' exp { $$ = $1/$3;}
	| '(' exp ')' { $$=$2; }
	|NUMBER	{$$=$1;}
	;
%%

int main() {
	printf("Enter the expression: ");
	yyparse();
	return 0;
}

int yyerror(char *s) {
	printf("Error: %s\n",s);
	return 0;
}
