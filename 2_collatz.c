// 23.10.8 20点03分
// homework
//  by HHC

#include <stdio.h>

int main()
{
    int input = 0, cnt = 0;
    scanf("%d", &input);
    int max = input;
    for (;;)
    {
        if (input % 2 == 0)
        {
            input /= 2;
        }
        else
        {
            input = input * 3 + 1;
        }
        cnt++;
        if (max < input)
        {
            max = input;
        }
        if (input == 1)
        {
            break;
        }
    }

    printf("%d %d", cnt, max);

    return 0;
}