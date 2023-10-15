// 23.10.14 12:23
// for homework
// by HHC

#include <stdio.h>

int main()
{
    int len = 0;
    scanf("%d", &len);

    getchar();

    char input[len];
    for (int i = 0; i < len; i++)
    {
        input[i] = getchar();
    }

    for (int i = 0; i < len; i++)
    {
        if (input[i] == '?')
        {
            input[i] = input[len - i - 1];
        }
    }

    for (int i = 0; i < len; i++)
    {

        printf("%c", input[i]);
    }

    return 0;
}