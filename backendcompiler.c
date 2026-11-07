#include<stdio.h>
#include<stdlib.h>

int main()
{
    FILE *fp;
    char result[10],arg1[10],arg2[10];
    char op;

    fp=fopen("input.txt","r");

    if(fp==NULL)
    {

    printf("FILE NOT FOUND!!!");
    return 0;
    }

    printf("8086 ASSEMBLY CODE:\n");
    while(fscanf(fp,"%s = %s %c %s\n",result,arg1,&op,arg2)==4)
    {
        printf("MOV AX,%s\n",arg1);

    if(op=='+')
    {
         printf("ADD AX,%s\n",arg2);
    }
    else if(op=='-')
    {
        printf("SUB AX,%s\n",arg2);
    }
    else if(op=='*')
    {
        printf(" MUL AX,%s\n",arg2);
    }
    else if(op=='/')
    {
         printf(" DIV AX,%s\n",arg2);
    }

    }
    printf("MOV %s,AX\n",result);

    fclose(fp);
return 0;
}