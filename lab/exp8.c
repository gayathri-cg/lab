#include<stdio.h>
#include<string.h>
char input[100];
int i=0;
int error=0;

void E();
void EDash();
void T();
void TDash();
void F();

void E() {
	T();
	EDash();
}

void EDash() {
	if (input[i] =='+') {
		i++;
		T();
		EDash();
	}
}

void T() {
	F();
	TDash();
}

void TDash() {
	if(input[i]=='*') {
		i++;
		F();
		TDash();
	}
}

void F() {
	if (input[i]=='(') {
		i++;
		E();
		if (input[i]==')'){
			i++;
		}
		else {
			error=1;
		}
	}
	else if ((input[i] >= 'a' && input[i] <= 'z') || (input[i] >='A' && input[i] <='Z'))  {
		i++;
	}
	else {
		error=1;
	}
}

int main() {
	printf("Enter the expression (use single letters as identifiers): ");
	scanf("%s", input);
	
	E();
	
	if (error==0 && input[i]=='\0') {
		printf("Input string is ACCEPTED\n");
	}
	else {
		printf("Input string is NOT ACCEPTED\n");
	}
	return 0;
}
