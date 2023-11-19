// 23.11.19
// for homework
// by HHC

#include <stdio.h>
#include <string.h>
#define MAX 10012
#define SPACE 12

int pointer = 1; // stack begin from 1;and always point to a empty unit
int stack[MAX] = {0};

int push(char word[]);
int pop();
int top();
int print();

int main()
{
    for (int i = 0; i < MAX; i++)
    {
        stack[i] = -1;
    }

    char order1[] = "push", order2[] = "pop",
         order3[] = "top", order4[] = "print";

    int n = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        char order[SPACE];
        memset(order, '0', SPACE);
        scanf("%s", order);
        if (strcmp(order, order1) == 0)
        {
            char word[SPACE];
            memset(word, '0', SPACE);
            scanf("%s", word);
            // printf("%c", word[0]);//for test
            push(word);
        }
        else if (strcmp(order, order2) == 0)
        {
            pop();
        }
        else if (strcmp(order, order3) == 0)
        {
            top();
        }
        else if (strcmp(order, order4) == 0)
        {
            print();
        }
    }

    return 0;
}

int push(char word[])
{
    stack[pointer++] = word[0];
    return 0;
}
int pop()
{
    if (pointer == 1)
    {
        printf("Empty\n");
        return 0;
    }
    else
    {
        stack[--pointer] = -1;
        return 0;
    }
}
int top()
{
    if (pointer == 1)
    {
        printf("Empty\n");
        return 0;
    }
    else
    {
        printf("%c\n", stack[pointer - 1]);
        return 0;
    }
}
int print()
{
    if (pointer == 1)
    {
        printf("Empty\n");
        return 0;
    }
    else
    {
        for (int i = pointer; i > 1; i--)
        {
            printf("| %c |\n", stack[i - 1]);
        }
        printf("|===|\n");
        return 0;
    }
}