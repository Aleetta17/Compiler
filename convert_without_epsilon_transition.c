
#include <stdio.h>

int n;
int e[10][10];          // Epsilon transitions
int trans[10][10];      // Input transitions
int closure[10][10];    // Epsilon closure
int result[10][10];     // Final transitions

void findClosure(int state, int start)
{
    int i;

    closure[start][state] = 1;

    for(i = 0; i < n; i++)
    {
        if(e[state][i] == 1 && closure[start][i] == 0)
            findClosure(i, start);
    }
}

int main()
{
    int i, j, k;

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("\nEnter epsilon transition table:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            scanf("%d", &e[i][j]);

    printf("\nEnter transition table for input symbol:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            scanf("%d", &trans[i][j]);

    /* Find epsilon closure of every state */
    for(i = 0; i < n; i++)
        findClosure(i, i);

    /* Find new transitions */
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            if(closure[i][j] == 1)
            {
                for(k = 0; k < n; k++)
                {
                    if(trans[j][k] == 1)
                        result[i][k] = 1;
                }
            }
        }
    }

    printf("\nNFA without epsilon transition:\n");

    for(i = 0; i < n; i++)
    {
        printf("q%d -> ", i);

        for(j = 0; j < n; j++)
        {
            if(result[i][j] == 1)
                printf("q%d ", j);
        }

        printf("\n");
    }

    return 0;
}
