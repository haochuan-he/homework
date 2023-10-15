// 23.10.11
// 附加题：阶层的和2
// by HHC

#include <stdio.h>
#define M 1000000007

int main(void)
{
    long long n = 0, mod = 1, sum = 0;
    scanf("%lld", &n);

    for (int i = 1; i <= n; i++)
    {
        mod = mod * i % M;
        sum = (sum + mod) % M;
    }

    printf("%lld", sum % M);

    return 0;
}