#include <stdio.h>

int n, m;

// Print one DFA state, e.g. {q0,q2}
void printSet(int s[]) {
    int k, first = 1;
    printf("{");
    for (k = 0; k < n; k++) {
        if (s[k] == 1) {
            if (first == 0) printf(",");
            printf("q%d", k);
            first = 0;
        }
    }
    if (first == 1) printf("NULL");
    printf("}");
}

int main() {
    int i, j, k, x;
    int nfa[10][10][10];    // nfa[i][j][k] = 1 if state i goes to state k on symbol j
    int dfa[1024][10];      // each DFA state: dfa[d][k] = 1 if it contains qk
    int trans[1024][10];    // DFA transition table
    int count = 1;          // number of DFA states so far

    printf("Enter number of states: ");
    scanf("%d", &n);
    printf("Enter number of symbols: ");
    scanf("%d", &m);

    // Read NFA (matrix form)
    printf("\nFor each state and symbol, enter %d values (1 = goes to that state, 0 = no)\n\n", n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            printf("q%d on symbol %d: ", i, j);
            for (k = 0; k < n; k++)
                scanf("%d", &nfa[i][j][k]);
        }
    }

    // Start state = {q0}
    for (k = 0; k < n; k++)
        dfa[0][k] = 0;
    dfa[0][0] = 1;

    // NFA to DFA conversion
    for (i = 0; i < count; i++) {
        for (j = 0; j < m; j++) {

            // Find the set of next states
            int next[10] = {0};
            for (k = 0; k < n; k++)
                if (dfa[i][k] == 1)
                    for (x = 0; x < n; x++)
                        if (nfa[k][j][x] == 1)
                            next[x] = 1;

            // Check if this set already exists
            int found = -1;
            for (k = 0; k < count; k++) {
                int same = 1;
                for (x = 0; x < n; x++)
                    if (dfa[k][x] != next[x])
                        same = 0;
                if (same == 1) {
                    found = k;
                    break;
                }
            }

            // If not, add it as a new DFA state
            if (found == -1) {
                for (x = 0; x < n; x++)
                    dfa[count][x] = next[x];
                found = count;
                count++;
            }

            trans[i][j] = found;
        }
    }

    // Print DFA table
    printf("\nDFA TRANSITION TABLE\nState\t\t");
    for (j = 0; j < m; j++)
        printf("%d\t\t", j);
    printf("\n");

    for (i = 0; i < count; i++) {
        printSet(dfa[i]);
        printf("\t\t");
        for (j = 0; j < m; j++) {
            printSet(dfa[trans[i][j]]);
            printf("\t\t");
        }
        printf("\n");
    }
    return 0;
}
