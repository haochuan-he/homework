// 23.10.27
// homework
// by HHC

#include <stdio.h>
#include <math.h>

int IsPrime(int number);
int Flip(int n);

int main()
{
    int n = 0, flip = 0, cnt = 0;
    scanf("%d", &n);

    for (int i = 2; i <= n; i++)
    {
        if (IsPrime(i) && IsPrime(Flip(i)))
        {
            cnt++;
        }
    }

    printf("%d", cnt);

    // // test
    // int num = Flip(n);
    // printf("%d", num);

    return 0;
}

int IsPrime(int number)
{
    for (int i = 2; i <= sqrt(number + 0.5); i++)
    {
        if (number % i == 0)
        {
            return 0;
        }
    }
    return 1;
}

int Flip(int n)
{
    if (n < 10)
    {
        return n;
    }
    int number = n;
    int digit = 0, tflip = 0;
    do
    {
        n /= 10;
        digit++;
    } while (n >= 10);

    for (int i = 0; i <= digit; i++)
    {
        tflip = tflip * 10 + (number % 10);
        number /= 10;
    }

    return tflip;
}