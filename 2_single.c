// 23.10.8 18点41分
// for homework
// by HHC

#include <stdio.h>

int main()
{
    int num[1000012] = {0};
    int total = 0;
    scanf("%d ", &total);

    for (int i = 0; i < (2 * total - 1); i++)
    {
        int number = -1;
        scanf("%d", &number);
        if (num[number] == 0)
        {
            num[number] = number;
        }
        else
        {
            num[number] = 0;
        }
    }

    int single = -2;
    for (int i = 0; i < 1000012; i++)
    {
        if (num[i] >= 1)
        {
            single = num[i];
            break;
        }
    }

    printf("%d", single);

    return 0;
}