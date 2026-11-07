#include <stdio.h>

int n;
int epsilon[20][20];
int visited[20];

void epsilonClosure(int state)
{
    int i;

    visited[state] = 1;
    printf("q%d ", state);

    for(i = 0; i < n; i++)
    {
        if(epsilon[state][i] == 1 && visited[i] == 0)
        {
            epsilonClosure(i);
        }
    }
}

int main()
{
    int i, j;

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter epsilon transition table (1 if epsilon transition exists else 0):\n");

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            scanf("%d", &epsilon[i][j]);
        }
    }

    printf("\nEpsilon Closures:\n");

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
            visited[j] = 0;

        printf("ε-closure(q%d) = { ", i);
        epsilonClosure(i);
        printf("}\n");
    }

    return 0;
}
