// 20.10.8 19点18分
// homework
//  by HHC

#include <stdio.h>

int main()
{
    const int M = 10007;
    int n = 0;
    scanf("%d", &n);
    int jiecheng_yu = 1, sum = 0;
    for (int i = 1; i <= n; i++)
    {
        jiecheng_yu = 1;
        for (int j = 1;
         j <= i;
          j++)
        {
            jiecheng_yu = j * jiecheng_yu % M;
        }
        sum = sum + jiecheng_yu;
    }

    printf("%d", sum % M);

    return 0;
}