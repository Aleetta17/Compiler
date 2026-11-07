#include <stdio.h>
#include <string.h>

char stack[100];
int top = -1;

void push(char c)
{
    stack[++top] = c;
    stack[top + 1] = '\0';
}

void showInput(char *input, int pos)
{
    if (input[pos] == '\0')
        printf("$");
    else
        printf("%s", input + pos);
}

int reduce()
{
    /* i -> E */
    if (top >= 0 && stack[top] == 'i')
    {
        stack[top] = 'E';
        stack[top + 1] = '\0';

        printf("%-10s %-10s Reduce i -> E\n", stack, "$");
        return 1;
    }

    /* (E) -> E */
    if (top >= 2 &&
        stack[top - 2] == '(' &&
        stack[top - 1] == 'E' &&
        stack[top] == ')')
    {
        top -= 2;
        stack[top] = 'E';
        stack[top + 1] = '\0';

        printf("%-10s %-10s Reduce (E) -> E\n", stack, "$");
        return 1;
    }

    /* E+E -> E */
    if (top >= 2 &&
        stack[top - 2] == 'E' &&
        stack[top - 1] == '+' &&
        stack[top] == 'E')
    {
        top -= 2;
        stack[top] = 'E';
        stack[top + 1] = '\0';

        printf("%-10s %-10s Reduce E+E -> E\n", stack, "$");
        return 1;
    }

    /* E*E -> E */
    if (top >= 2 &&
        stack[top - 2] == 'E' &&
        stack[top - 1] == '*' &&
        stack[top] == 'E')
    {
        top -= 2;
        stack[top] = 'E';
        stack[top + 1] = '\0';

        printf("%-10s %-10s Reduce E*E -> E\n", stack, "$");
        return 1;
    }

    return 0;
}

int main()
{
    char input[100];
    int i = 0;

    printf("Enter expression (use i for id): ");
    scanf("%s", input);

    printf("\n%-10s %-10s %s\n", "Stack", "Input", "Action");

    while (input[i] != '\0')
    {
        /* SHIFT */
        push(input[i]);

        printf("%-10s ", stack);
        showInput(input, i + 1);
        printf("       Shift %c\n", input[i]);

        i++;

        /* REDUCE */
        while (reduce())
        {
            /* Continue reducing */
        }
    }

    /* ACCEPT */
    if (top == 0 && stack[0] == 'E')
    {
        printf("%-10s %-10s Accept\n", stack, "$");
        printf("\nAccepted\n");
    }
    else
    {
        printf("%-10s %-10s Reject\n", stack, "$");
        printf("\nRejected\n");
    }

    return 0;
}
