#include<stdio.h>
#include<string.h>
#include<ctype.h>

void FIRST(char res[], char c);
void addToResult(char res[], char val);

int nop;
char prod[10][10];

int main() {
	int i;
	char choice;
	char c;
	char res1[20];
	
	printf("Enter number of productions: ");
	scanf("%d", &nop);
	
	printf("Enter productions in the forms E=E+T (use $ for epsilon)\n");
	for (i=0;i<nop;i++) {
		printf("Enter production number %d: ", i+1);
		scanf("%s", prod[i]);
	}
	
	do{
		printf("\nFind the FIRST of: ");
		scanf(" %c", &c);
		
		res1[0]='\0';
		FIRST(res1,c);
		
		printf("FIRST(%c) = { ", c );
		for (i=0; res1[i]!='\0';i++){
			printf("%c ", res1[i]);
		}
		printf("}\n");
		
		printf("Press 'y' to continue: ");
		scanf(" %c",&choice);
	} while(choice=='y'||choice=='Y');
	
	return 0;
}

void FIRST(char res[], char c) {
	int i,j,k;
	char subres[10];
	int eps;
	
	res[0] = '\0';
	
	if(!(isupper(c))) {
		addToResult(res,c);
		return;
	}
	
	for (i=0;i<nop;i++) {
		if(prod[i][0]==c) {
			if (prod[i][2] =='$') {
				addToResult(res,'$');
			}
			else {
				j=2;
				while(prod[i][j] !='\0') {
					eps=0;
					subres[0] ='\0';
					
					FIRST(subres, prod[i][j]);
					
					for (k=0; subres[k]!='\0';k++)
						addToResult(res, subres[k]);
						
					for (k=0; subres[k]!='\0';k++){
						if(subres[k]=='$') {
							eps=1;
							break;
						}
					}
					
					if(!eps)
						break;
						
					j++;
				}
			}
		}
	}
}

void addToResult(char res[], char val) {
	int k;
	for(k=0;res[k]!='\0';k++)
		if(res[k]==val)
			return;
	res[k]=val;
	res[k+1]='\0';
}
