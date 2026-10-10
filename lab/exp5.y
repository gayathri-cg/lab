%{
#include<stdio.h>
#include<stdlib.h>
int yylex(void);
void yyerror(char *s);
%}

%token NUMBER ID

%left '+''-'
%left '*''/'

%%
exp: exp '+' exp
	|exp '-' exp
	|exp '*' exp
	|exp '/' exp
	|'(' exp ')'
	|NUMBER
	|ID
	;
%%

int main(){
	printf("Enter the expession: ");
	yyparse();
	printf("Valid Expression!\n");
	return 0;
}

void yyerror(char *s) {
	printf("Invalid Expression!\n");
	exit(0);
}
