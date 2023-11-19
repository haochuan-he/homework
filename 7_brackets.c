// 23.11.17
// for homework
// by HHC

#include <stdio.h>
#include <string.h>
#define MAX 100012 // 100012
// out(1) [2] {3}in
int in(int stack[], int now[], int kind);
int out(int stack[], int now[], int kind);
int main()
{
    int t = 0;
    scanf("%d", &t);

    char str[MAX];
    int stack[MAX] = {0};
    // loop for t times
    for (int i = 0; i < t; i++)
    {
        memset(str, '0', MAX);
        memset(stack, 0, MAX);
        scanf("%s", str);
        int len = strlen(str);
        int flag = 0;
        int now[] = {0};

        for (int i = len - 1; i >= 0; i--)
        {

            if (str[i] == '(' || str[i] == '[' || str[i] == '{')
            {
                if (out(stack, now, str[i]))
                {
                    flag = 1;
                    break;
                }
            }
            else // if (str[i] == ')' || str[i] == ']' || str[i] == '}')
            {
                in(stack, now, (str[i] == ')') ? '(' : (str[i] - 2));
                // if (in(stack, now, str[i]))
                // {
                //     flag = 1;
                //     break;
                // }
            }
        }

        if (flag)
        {
            printf("False\n");
        }
        else
        {
            printf("True\n");
        }
    }

    return 0;
}

int in(int stack[], int now[], int kind)
{
    stack[now[0]++] = kind;
    return 0;
}
int out(int stack[], int now[], int kind)
{
    if (stack[--now[0]] != kind || now[0] < 0)
    {
        return 1;
    }
    else
    {
        stack[now[0]] = 0;
        return 0;
    }
}