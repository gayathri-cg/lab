%{
#include<stdio.h>
int sc=0,wc=0,lc=0,cc=0;
%}
%%
[\n] { lc++; wc++;}
[\t] { sc++; wc++;}
[" "] { sc++; wc++;}
[^\n\t ]+ {cc+=yyleng;}
%%
void main()
{
printf("Enter the input:\n");
yylex();
printf("The number of lines=%d\n",lc);
printf("The number of spaces=%d\n",sc);
printf("The number of words=%d\n",wc);
printf("The number of characters are=%d\n",cc);
}
int yywrap( )

{
return 1;
}
