#include<stdio.h>
#include<string.h>
#include<ctype.h>
void main()
{
FILE *f1;
char c;
char str[20];
int i=0,num,linecount=1;
f1=fopen("input.txt","r");
while((c=getc(f1))!=EOF)
{
if(isdigit(c))
{
num=c-48;
c=getc(f1);
while(isdigit(c))
{
num=num*10+(c-48);
c=getc(f1);
}
printf("%d is a number \n",num);
ungetc(c,f1); /* <-- FIX: push back the delimiter */
}
else if(isalpha(c))
{
str[i++]=c;
c=getc(f1);

while(isdigit(c)||isalpha(c)||c=='_'||c=='$')
{
str[i++]=c;
c=getc(f1);
}
str[i++]='\0';

if(strcmp("for",str)==0||strcmp("while",str)==0||strcmp("do",str)==0||strcmp("int",str)==0||strcmp("float",str)==0||strcmp("char",str)==0||strcmp("double",str)==0||strcmp("static",str)==0||strcmp("switch",str)==0||strcmp("case",str)==0)
{
printf("%s is a keyword\n",str);
}
else
printf("%s is a identifier\n",str);
ungetc(c,f1);
i=0;
}
else if(c==' '||c=='\t')
{ }
else if(c=='\n')
linecount++;
else
printf("%c is a special symbol\n",c);
}
printf("Total no. of lines are: %d\n",linecount);
fclose(f1);
}
