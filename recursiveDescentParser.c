#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char input[100];
int pos = 0;

void E();
void Eprime();
void T();
void Tprime();
void F();

void error() {
    printf("Invalid expression\n");
    exit(1);
}

void match(char expected) {
    if (input[pos] == expected)
        pos++;
    else
        error();
}

/* E -> T E' */
void E() {
    T();
    Eprime();
}

/* E' -> + T E' | epsilon */
void Eprime() {
    if (input[pos] == '+') {
        match('+');
        T();
        Eprime();
    }
}

/* T -> F T' */
void T() {
    F();
    Tprime();
}

/* T' -> * F T' | epsilon */
void Tprime() {
    if (input[pos] == '*') {
        match('*');
        F();
        Tprime();
    }
}

/* F -> ( E ) | id */
void F() {
    if (isalpha(input[pos])) {
        // id
        pos++;
    }
    else if (input[pos] == '(') {
        match('(');
        E();
        match(')');
    }
    else {
        error();
    }
}

int main() {
    printf("Enter an expression: ");
    scanf("%s", input);

    E();

    if (input[pos] == '\0')
        printf("Valid expression\n");
    else
        printf("Invalid expression\n");

    return 0;
}

