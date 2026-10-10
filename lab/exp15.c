#include <stdio.h>

int n, m;
int nfa[10][10];
int dst[1024];
int dt[1024][10];
int nd = 1;
char sym[10];

int main()
{
    int i, j, k, t;
    int from, to, nt, s, nf;
    int fin = 0, mask;
    char c;

    printf("Number of states and symbols: ");
    scanf("%d %d", &n, &m);

    printf("Symbols: ");
    for (k = 0; k < m; k++)
        scanf(" %c", &sym[k]);

    printf("Number of transitions, then 'from symbol to' for each:\n");
    scanf("%d", &nt);

    while (nt--) {
        scanf("%d %c %d", &from, &c, &to);

        for (k = 0; k < m; k++) {
            if (sym[k] == c)
                nfa[from][k] |= 1 << to;
        }
    }

    printf("Start state, number of final states, final states: ");
    scanf("%d %d", &s, &nf);

    while (nf--) {
        scanf("%d", &t);
        fin |= 1 << t;
    }

    /* DFA state = set of NFA states */
    dst[0] = 1 << s;

    for (i = 0; i < nd; i++) {

        for (k = 0; k < m; k++) {

            /* Move from current DFA state on symbol k */
            for (mask = 0, j = 0; j < n; j++) {
                if ((dst[i] >> j) & 1)
                    mask |= nfa[j][k];
            }

            /* Find whether this DFA state already exists */
            for (t = 0; t < nd && dst[t] != mask; t++)
                ;

            /* Add new DFA state */
            if (t == nd && mask)
                dst[nd++] = mask;

            /* Store transition */
            dt[i][k] = mask ? t : -1;
        }
    }

    printf("\nDFA:\n");
    printf("State NFA set ");

    for (k = 0; k < m; k++)
        printf("%c ", sym[k]);

    for (i = 0; i < nd; i++) {

        /* Print * for final DFA states */
        printf("\n%s%c {",
               (dst[i] & fin) ? "*" : " ",
               'A' + i);

        /* Print NFA states contained in this DFA state */
        for (j = 0; j < n; j++) {
            if ((dst[i] >> j) & 1)
                printf("q%d ", j);
        }

        printf("}\t");

        /* Print DFA transitions */
        for (k = 0; k < m; k++) {
            if (dt[i][k] < 0)
                printf("- ");
            else
                printf("%c ", 'A' + dt[i][k]);
        }
    }

    printf("\n");
    printf("(* = final state, A = start state, - = no move)\n");

    return 0;
}
