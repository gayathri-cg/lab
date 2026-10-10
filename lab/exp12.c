#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
char ip_sym[15], stack[15];
int ip_ptr = 0, st_ptr = 0, len, i;
char temp[2], temp2[2];
char act[15];
void check();
int main()
{
    printf("\n\t\tSHIFT REDUCE PARSER\n");
    printf("\nGrammar\n");
    printf("\n E -> E+E");
    printf("\n E -> E-E");
    printf("\n E -> E*E");
    printf("\n E -> E/E");
    printf("\n E -> a | b\n");
    printf("\nEnter the input string: ");
    scanf(" %14[^\n]", ip_sym);
    printf("\n\tStack Implementation Table");
    printf("\n Stack\t\tInput Symbol\t\tAction");
    printf("\n ______\t\t____________\t\t______\n");
    printf("\n $\t\t%s$\t\t\t--", ip_sym);
    len = strlen(ip_sym);
    strcpy(act, "shift ");
    temp[0] = ip_sym[ip_ptr];
    temp[1] = '\0';
    strcat(act, temp);
    for (i = 0; i <= len - 1; i++)
    {
        stack[st_ptr] = ip_sym[ip_ptr];
        stack[st_ptr + 1] = '\0';
        ip_sym[ip_ptr] = ' ';
        ip_ptr++;
        printf("\n $%s\t\t%s$\t\t\t%s", stack, ip_sym, act);
        strcpy(act, "shift ");
        temp[0] = ip_sym[ip_ptr];
        temp[1] = '\0';
        strcat(act, temp);
        check();
        st_ptr++;
    }
    check();
    return 0;
}
void check()
{
    int flag = 0;
    temp2[0] = stack[st_ptr];
    temp2[1] = '\0';
    if (isalpha((unsigned char)temp2[0]))
    {
        stack[st_ptr] = 'E';
        printf("\n $%s\t\t%s$\t\t\tE->%s", stack, ip_sym, temp2);
        flag = 1;
    }
    if (!strcmp(temp2, "+") ||
        !strcmp(temp2, "*") ||
        !strcmp(temp2, "/") ||
        !strcmp(temp2, "-"))
    {
        flag = 1;
    }
    if (!strcmp(stack, "E+E") ||
        !strcmp(stack, "E-E") ||
        !strcmp(stack, "E*E") ||
        !strcmp(stack, "E/E"))
    {
        if (!strcmp(stack, "E+E"))
        {
            strcpy(stack, "E");
            printf("\n $%s\t\t%s$\t\t\tE->E+E", stack, ip_sym);
        }
        else if (!strcmp(stack, "E-E"))
        {
            strcpy(stack, "E");
            printf("\n $%s\t\t%s$\t\t\tE->E-E", stack, ip_sym);
        }
        else if (!strcmp(stack, "E/E"))
        {
            strcpy(stack, "E");
            printf("\n $%s\t\t%s$\t\t\tE->E/E", stack, ip_sym);
        }
        else
        {
            strcpy(stack, "E");
            printf("\n $%s\t\t%s$\t\t\tE->E*E", stack, ip_sym);
        }
        flag = 1;
        st_ptr = 0;
    }
    if (!strcmp(stack, "E") && ip_ptr == len)
    {
        printf("\n $%s\t\t%s$\t\t\tACCEPT", stack, ip_sym);
        exit(0);
    }
    if (flag == 0)
    {
        printf("\n $%s\t\t%s$\t\t\tREJECT", stack, ip_sym);
        exit(0);
    }
}
