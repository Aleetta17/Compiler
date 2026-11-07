#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct variable
{
    char name[10];
    int value;
    int constant;
};

struct variable v[20];
int n = 0;

int find(char name[])
{
    int i;

    for (i = 0; i < n; i++)
    {
        if (strcmp(v[i].name, name) == 0)
            return i;
    }

    return -1;
}

int main()
{
    int i, pos;
    char left[10], right[10];
    int value;

    printf("Enter number of statements: ");
    scanf("%d", &n);

    printf("Enter statements:\n");

    for (i = 0; i < n; i++)
    {
        scanf("%s = %s", left, right);

        strcpy(v[i].name, left);

        if (right[0] >= '0' && right[0] <= '9')
        {
            v[i].value = atoi(right);
            v[i].constant = 1;
        }
        else
        {
            pos = find(right);

            if (pos != -1 && v[pos].constant == 1)
            {
                v[i].value = v[pos].value;
                v[i].constant = 1;
            }
            else
            {
                v[i].constant = 0;
            }
        }
    }

    printf("\nAfter Constant Propagation:\n");

    for (i = 0; i < n; i++)
    {
        if (v[i].constant == 1)
            printf("%s = %d\n", v[i].name, v[i].value);
        else
            printf("%s = variable\n", v[i].name);
    }

    return 0;
}
