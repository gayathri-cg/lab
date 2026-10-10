#include<stdio.h>
#include<string.h>
int main() {
	char stack[20], ip[20], opt[10][10][2], ter[10];
	int i , j, n, top=0, col=0, row=0,k;
	
	for ( i=0;i<20;i++){
		stack[i]='\0';
		ip[i] = '\0';
	}
	for(i=0;i<10;i++) 
		for(j=0;j<10;j++)
			opt[i][j][0] ='\0';
			
	printf("Enter the no. of terminals: ");
	scanf("%d", &n);
	
	printf("\nEnter the terminals: ");
	scanf(" %s", ter);
	
	printf("\nEnter the table values:\n");
	for(i=0;i<n;i++) {
		for(j=0;j<n;j++) {
			printf("Enter the values for %c %c: ", ter[i], ter[j]);
			scanf(" %s", opt[i][j]);
		}
	}
	
	printf("\nOPERATOR PRECEDENCE TABLE:\n");
	printf("\t");
	for(i=0;i<n;i++)
		printf("%c\t", ter[i]);
	printf("\n");
	
	for(i=0;i<n;i++){
		printf("%c\t", ter[i]);
		for(j=0;j<n;j++)
			printf("%c\t", opt[i][j][0]);
		printf("\n");
	}
	
	stack[top] ='$';
	
	printf("\nEnter the input string: ");
	scanf(" %s", ip);
	strcat(ip,"$");
	i=0;
	
	printf("\n%-25s%-25s%-25s\n", "STACK","INPUT STRING", "ACTION");
	printf("%-25s%-25s%-25s\n", stack, ip, "");
	
	while(i<=(int)strlen(ip)){
		for(k=0;k<n;k++) {
			if(stack[top] == ter[k])
				row=k;
			if(ip[i]==ter[k])
				col=k;
		}
		if(stack[top] =='$' && ip[i] =='$') {
			printf("\nString is accepted\n");
			break;
		}
		
		else if(opt[row][col][0] =='<' || opt[row][col][0]=='=') {
			stack[++top] = opt[row][col][0];
			stack[++top] = ip[i];
			printf("Shift %c", ip[i]);
			i++;
		}
		else if (opt[row][col][0]=='>') {
			while(stack[top]!='<')
				top--;
			top--;
			printf("Reduce");
		}
		else {
			printf("\nString is not accepted\n");
			break;
		}
		
		printf("\n");
		for(k=0;k<=top;k++)
			printf("%c", stack[k]);
		printf("\t\t\t");
		for(k=i;k<(int)strlen(ip);k++)
			printf("%c", ip[k]);
		printf("\t\t\t");
	}
	return 0;
}
