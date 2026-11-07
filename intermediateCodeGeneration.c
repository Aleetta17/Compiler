#include <stdio.h>
#include <string.h>
#include <ctype.h>

char stack[50];
int top = -1;
int temp = 1;

void push(char c)
{
    stack[++top] = c;
}

char pop()
{
    return stack[top--];
}

int precedence(char c)
{
    if (c == '+' || c == '-')
        return 1;

    if (c == '*' || c == '/')
        return 2;

    return 0;
}

void infixToPostfix(char infix[], char postfix[])
{
    int i, j = 0;
    char c;

    for (i = 0; infix[i] != '\0'; i++)
    {
        c = infix[i];

        if (isalnum(c))
        {
            postfix[j++] = c;
        }
        else if (c == '(')
        {
            push(c);
        }
        else if (c == ')')
        {
            while (top != -1 && stack[top] != '(')
                postfix[j++] = pop();

            if (top != -1)
                pop();
        }
        else
        {
            while (top != -1 &&
                   stack[top] != '(' &&
                   precedence(stack[top]) >= precedence(c))
            {
                postfix[j++] = pop();
            }

            push(c);
        }
    }

    while (top != -1)
        postfix[j++] = pop();

    postfix[j] = '\0';
}

void generateCode(char postfix[])
{
    char s[50][10];
    int top2 = -1;
    int i;
    char op;
    char a[10], b[10], result[10];

    for (i = 0; postfix[i] != '\0'; i++)
    {
        if (isalnum(postfix[i]))
        {
            s[++top2][0] = postfix[i];
            s[top2][1] = '\0';
        }
        else
        {
            op = postfix[i];

            if (top2 < 1)
            {
                printf("Invalid expression\n");
                return;
            }

            strcpy(b, s[top2--]);
            strcpy(a, s[top2--]);

            sprintf(result, "t%d", temp++);

            printf("%s = %s %c %s\n", result, a, op, b);

            strcpy(s[++top2], result);
        }
    }

    if (top2 == 0)
        printf("Result = %s\n", s[top2]);
}

int main()
{
    char expression[50];
    char postfix[50];

    printf("Enter expression: ");
    scanf("%s", expression);

    infixToPostfix(expression, postfix);

    printf("\nIntermediate Code:\n");

    if (strchr(expression, '+') ||
        strchr(expression, '-') ||
        strchr(expression, '*') ||
        strchr(expression, '/'))
    {
        generateCode(postfix);
    }
    else
    {
        printf("No operator found. Enter an expression like a+b*c\n");
    }

    return 0;
}
