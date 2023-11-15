// 23.11.12
// for homework
// by HHC

#include <stdio.h>

int Aunts(int n);
int main()
{
    int n;
    scanf("%d", &n);
    printf("%d", Aunts(n));

    return 0;
}

int Aunts(int n)
{
    if (n <= 3)
    {
        return n;
    }

    return Aunts(n - 1) + Aunts(n - 2);
}