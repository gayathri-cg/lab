%{
#include<stdio.h>
int vcount = 0;
int ccount = 0;
%}
%%
[aeiouAEIOU] { vcount++; }
[a-zA-Z] { ccount++; }
\n { /* ignore newline, or use ECHO; if you want it printed */ }
. { /* ignore other characters like spaces, digits, punctuation */ }

%%
int main()
{
printf("Enter the string of vowels and consonants: ");
yylex();
printf("Number of vowels are: %d\n", vcount);
printf("Number of consonants are: %d\n", ccount);
return 0;
}
int yywrap()
{
return 1;
}
