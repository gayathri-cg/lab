#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 50

struct expr {
    char op[4], op1[16], op2[16], res[16];
    int flag;
} arr[MAX];

int n;

int is_const(const char *s)
{
    int i = 0;
    if (s[0] == '-' && s[1] != '\0')
        i = 1;
    if (s[i] == '\0')
        return 0;
    for (; s[i]; i++)
        if (!isdigit((unsigned char)s[i]))
            return 0;
    return 1;
}

void input(void)
{
    int i;
    printf("\nEnter the number of expressions : ");
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Invalid number (1 to %d allowed)\n", MAX);
        exit(1);
    }

    printf("\nEnter the input (op op1 op2 result), use '.' as op2 for '=' :\n");

    for (i = 0; i < n; i++) {
        if (scanf("%3s %15s %15s %15s",
                  arr[i].op, arr[i].op1, arr[i].op2, arr[i].res) != 4) {
            printf("Bad input\n");
            exit(1);
        }
        arr[i].flag = 0;
    }
}

void change(int p, const char *val)
{
    int i;

    for (i = p + 1; i < n; i++) {
        if (strcmp(arr[p].res, arr[i].op1) == 0)
            strcpy(arr[i].op1, val);

        if (strcmp(arr[i].op, "=") != 0 &&
            strcmp(arr[p].res, arr[i].op2) == 0)
            strcpy(arr[i].op2, val);

        if (strcmp(arr[p].res, arr[i].res) == 0)
            break;
    }
}

void constant(void)
{
    int i, a, b, r, ok;
    char val[16];

    for (i = 0; i < n; i++) {
        char op = arr[i].op[0];
        ok = 0;

        if (strcmp(arr[i].op, "=") == 0) {
            if (is_const(arr[i].op1)) {
                r = atoi(arr[i].op1);
                ok = 1;
            }
        } else if (strlen(arr[i].op) == 1 &&
                   is_const(arr[i].op1) &&
                   is_const(arr[i].op2)) {
            a = atoi(arr[i].op1);
            b = atoi(arr[i].op2);
            ok = 1;

            switch (op) {
                case '+':
                    r = a + b;
                    break;
                case '-':
                    r = a - b;
                    break;
                case '*':
                    r = a * b;
                    break;
                case '/':
                    if (b == 0)
                        ok = 0;
                    else
                        r = a / b;
                    break;
                default:
                    ok = 0;
            }
        }

        if (ok) {
            sprintf(val, "%d", r);
            arr[i].flag = 1;
            change(i, val);
        }
    }
}

void output(void)
{
    int i;

    printf("\nOptimized code is :");

    for (i = 0; i < n; i++)
        if (!arr[i].flag)
            printf("\n%s %s %s %s",
                   arr[i].op, arr[i].op1, arr[i].op2, arr[i].res);

    printf("\n");
}

int main(void)
{
    input();
    constant();
    output();
    return 0;
}
