#include<stdio.h>
#include<string.h>
#include<ctype.h>

int nop, m=0;
int gi, gj;
char prod[10][10], res[10];

void FOLLOW(char c);
void first(char c);
void result(char c);

int main() {
	int i, choice;
	char c, ch;
	
	printf("Enter the no. of productions: ");
	scanf("%d", &nop);
	
	printf("Enter the production string like E=E+T (use $ for epsilon)\n");
	
	for(i=0; i<nop; i++) {
		printf("Enter production number %d: ", i+1);
		scanf(" %s", prod[i]);
	}
	
	do {
		m=0;
		printf("\nFind FOLLOW of --> ");
		scanf(" %c", &c);
		
		FOLLOW(c);
		
		printf("FOLLOW(%c) = { ",c);
		for(i=0;i<m;i++)
			printf("%c ", res[i]);
		printf("}\n");
		
		printf("Do you want to continue (press 1 to continue)? ");
		scanf("%d%c", &choice, &ch);
		
	}while(choice==1);
	return 0;
}

void FOLLOW(char c) {
	if (prod[0][0] ==c)
		result('$');
	for (gi=0;gi<nop;gi++) {
		for (gj=2;gj<(int)strlen(prod[gi]);gj++) {
			if(prod[gi][gj] ==c) {
				if(prod[gi][gj+1]!='\0') {
					first(prod[gi][gj+1]);
				}
				else if(c!=prod[gi][0]) {
					FOLLOW(prod[gi][0]);
				}
			}
		}
	}
}

void first(char c) {
	int k;
	
	if(!(isupper(c))) {
		result(c);
		return;
	}
	
	for(k=0;k<nop;k++) {
		if(prod[k][0]==c){
			if(prod[k][2]=='$') {
			FOLLOW(prod[gi][0]);
			}
			else if(!isupper(prod[k][2])) {
				result(prod[k][2]);
			}
			else{
				first(prod[k][2]);
			}
		}
	}
}

void result(char c) {
	int i;
	for (i=0;i<m;i++)
		if(res[i]==c)
			return;
	res[m++]=c;
}
