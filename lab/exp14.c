#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXQ 50
#define MAXV 100
#define LEN 32

char icode[MAXQ][LEN];       /* quadruples such as a=b+c */
char vars[MAXV][LEN];        /* distinct variable names */
int nq = 0, nv = 0;

/* 1 if s is an integer constant (optionally negative) */
int is_number(const char *s)
{
    int i = 0;

    if (s[0] == '-' && s[1])
        i = 1;

    if (!s[i])
        return 0;

    for (; s[i]; i++)
        if (!isdigit((unsigned char)s[i]))
            return 0;

    return 1;
}

/* Case-insensitive equality
   (MASM/TASM names are not case sensitive) */
int ieq(const char *a, const char *b)
{
    while (*a && *b) {
        if (tolower((unsigned char)*a) !=
            tolower((unsigned char)*b))
            return 0;

        a++;
        b++;
    }

    return *a == *b;
}

/* Add variable if it is not already present */
void add_var(const char *s)
{
    int i;

    if (is_number(s))
        return;

    for (i = 0; i < nv; i++)
        if (ieq(vars[i], s))
            return;

    if (nv < MAXV)
        strcpy(vars[nv++], s);
}

/* Copy n characters and terminate.
   Returns 0 if too long or empty. */
int copy_n(char *dst, const char *src, int n)
{
    if (n <= 0 || n >= LEN)
        return 0;

    strncpy(dst, src, n);
    dst[n] = '\0';

    return 1;
}

/*
   Parse:
       res=a
       res=-a
       res=a op b

   op:
       0 = plain assignment
       'n' = unary minus
       + - * / = binary operation
*/
int parse(const char *line, char *res, char *a, char *op, char *b)
{
    const char *eq = strchr(line, '=');
    const char *rhs;
    const char *p;

    if (!eq || !copy_n(res, line, (int)(eq - line)))
        return 0;

    rhs = eq + 1;

    if (!*rhs)
        return 0;

    /*
       Start at rhs + 1 so that a leading '-' can
       represent unary minus.
    */
    for (p = rhs + 1; *p; p++) {
        if (strchr("+-*/", *p))
            break;
    }

    if (*p) {
        /* Binary operation */
        *op = *p;

        return copy_n(a, rhs, (int)(p - rhs)) &&
               copy_n(b, p + 1, (int)strlen(p + 1));
    }

    /* Unary minus on a variable */
    if (rhs[0] == '-' && !is_number(rhs)) {
        *op = 'n';

        return copy_n(a,
                      rhs + 1,
                      (int)strlen(rhs + 1));
    }

    /* Simple assignment */
    *op = 0;

    return copy_n(a, rhs, (int)strlen(rhs));
}

int main(void)
{
    int i;

    char res[LEN];
    char a[LEN];
    char b[LEN];
    char op;

    printf("Enter the set of intermediate code ");
    printf("(terminated by exit):\n");

    /* Read intermediate code */
    while (nq < MAXQ &&
           scanf("%31s", icode[nq]) == 1) {

        if (strcmp(icode[nq], "exit") == 0)
            break;

        nq++;
    }

    /*
       Pass 1:
       Collect variables for the DATA segment.
    */
    for (i = 0; i < nq; i++) {

        b[0] = '\0';

        if (!parse(icode[i], res, a, &op, b)) {
            printf("Invalid quadruple: %s\n",
                   icode[i]);
            return 1;
        }

        add_var(res);
        add_var(a);

        if (op && op != 'n')
            add_var(b);
    }

    /*
       Generate 8086 assembly program.
    */
    printf("\nTarget Code Generation (8086)\n");
    printf("*****************************\n");

    printf(".MODEL SMALL\n");
    printf(".STACK 100H\n");
    printf(".DATA\n");

    for (i = 0; i < nv; i++)
        printf("    %s DW 0\n", vars[i]);

    printf(".CODE\n");
    printf("MAIN PROC\n");
    printf("    MOV AX, @DATA\n");
    printf("    MOV DS, AX\n");

    /*
       Pass 2:
       Generate target code.
    */
    for (i = 0; i < nq; i++) {

        parse(icode[i], res, a, &op, b);

        printf("\n    ; %s\n", icode[i]);

        switch (op) {

            case 0:
                /* res = a */
                printf("    MOV AX, %s\n", a);
                printf("    MOV %s, AX\n", res);
                break;

            case 'n':
                /* res = -a */
                printf("    MOV AX, %s\n", a);
                printf("    NEG AX\n");
                printf("    MOV %s, AX\n", res);
                break;

            case '+':
                /* res = a + b */
                printf("    MOV AX, %s\n", a);
                printf("    ADD AX, %s\n", b);
                printf("    MOV %s, AX\n", res);
                break;

            case '-':
                /* res = a - b */
                printf("    MOV AX, %s\n", a);
                printf("    SUB AX, %s\n", b);
                printf("    MOV %s, AX\n", res);
                break;

            case '*':
                /* res = a * b */
                printf("    MOV AX, %s\n", a);
                printf("    MOV BX, %s\n", b);
                printf("    IMUL BX\n");
                printf("    MOV %s, AX\n", res);
                break;

            case '/':
                /* res = a / b */
                printf("    MOV AX, %s\n", a);
                printf("    CWD\n");
                printf("    MOV BX, %s\n", b);
                printf("    IDIV BX\n");
                printf("    MOV %s, AX\n", res);
                break;

            default:
                printf("    ; Unknown operation\n");
                break;
        }
    }

    /* Program termination */
    printf("\n");
    printf("    MOV AH, 4CH\n");
    printf("    INT 21H\n");

    printf("MAIN ENDP\n");
    printf("END MAIN\n");

    return 0;
}
