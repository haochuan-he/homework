// 23.10.14
// homework
// by HHC

#include <stdio.h>

int main()
{
    int len = 0;
    scanf("%d", &len);
    int num[len + 1];

    for (int i = 1; i < len + 1; i++)
    {
        num[i] = 0;
    }

    for (int i = 1; i < len + 1; i++)
    {
        for (int k = 1; i * k < len; k++)
        {
            if (num[i * k] == 1)
            {
                num[i * k] = 0;
            }
            else
            {
                num[i * k] = 1;
            }
        }
    }

    for (int i = 1; i < len + 1; i++)
    {
        if (num[i] == 1)
        {
            printf("%d ", i);
        }
    }

    return 0;
}