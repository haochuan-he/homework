// 23.10.27
// homework
// by HHC

#include <stdio.h>

int main()
{
    int n = 0, t = 0, num = 0, sum = 0;
    scanf("%d%d", &n, &t);
    num = t;
    while (n--)
    {
        sum = sum + num;
        num = num * 10 + t;
    }
    printf("%d", sum);

    return 0;
}