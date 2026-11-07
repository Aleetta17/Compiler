#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isKeyword(char word[])
{
    char keywords[][10] = {"int","char","float","if","else","while","for","return","void"};

    for(int i=0; i<9; i++)
        if(strcmp(word, keywords[i]) == 0)
            return 1;

    return 0;
}

int main()
{
    FILE *fp = fopen("input.txt", "r");
    char word[50];
    int ch, i, line=1, tokenNo=1;

    if(fp == NULL)
    {
        printf("File not found");
        return 0;
    }

    printf("%-8s %-8s %-18s %s\n", "Line", "Token", "Type", "Lexeme");
    printf("-----------------------------------------------------\n");

    while((ch = fgetc(fp)) != EOF)
    {
        if(ch == '\n')
        {
            line++;
            continue;
        }

        if(isspace(ch))
            continue;

        if(isalpha(ch))
        {
            i=0;
            do {
                word[i++] = ch;
                ch = fgetc(fp);
            } while(isalnum(ch));

            word[i]='\0';
            if(ch != EOF) ungetc(ch, fp);

            printf("%-8d %-8d %-18s %s\n", line, tokenNo++,
                   isKeyword(word) ? "Keyword" : "Identifier", word);
        }

        else if(isdigit(ch))
        {
            i=0;
            do {
                word[i++] = ch;
                ch = fgetc(fp);
            } while(isdigit(ch));

            word[i]='\0';
            if(ch != EOF) ungetc(ch, fp);

            printf("%-8d %-8d %-18s %s\n", line, tokenNo++, "Number", word);
        }

        else if(ch == '"')
        {
            i=0;
            word[i++] = '"';

            while((ch=fgetc(fp)) != '"' && ch != EOF)
                word[i++] = ch;

            if(ch == '"') word[i++] = '"';
            word[i]='\0';

            printf("%-8d %-8d %-18s %s\n", line, tokenNo++, "String Literal", word);
        }

        else if(strchr("+-*/=", ch))
            printf("%-8d %-8d %-18s %c\n", line, tokenNo++, "Operator", ch);

        else if(strchr(";,(){}", ch))
            printf("%-8d %-8d %-18s %c\n", line, tokenNo++, "Special Symbol", ch);
    }

    fclose(fp);
    return 0;
}
