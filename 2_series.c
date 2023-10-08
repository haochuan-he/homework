// 23.10.8 19点47分
// homework
//  by HHC

#include <stdio.h>
#include <math.h>

int main()
{
    double x = 0, sum = 0;
    int n = 0;

    scanf("%lf %d", &x, &n);

    for (int i = 0; i <= n; i++)
    {
        sum += pow(-1.0, i) * pow(x, 2 * i + 1) / (2 * i + 1);
    }

    printf("%.10lf", sum * 4.0);

    return 0;
}