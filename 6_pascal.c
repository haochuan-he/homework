// 23.11.12
// for homework
//  by HHC

#include <stdio.h>

int YangHui(int a, int b);

int main()
{
    int a, b;
    scanf("%d%d", &a, &b);
    printf("%d", YangHui(a - 1, b - 1));

    return 0;
}

int YangHui(int a, int b)
{ // the smallest task
    if (b == 1 || b == a - 1)
    {
        return a;
    }
    else if (b == 0 || a == b)
    {
        return 1;
    }

    // find the smaller task
    return YangHui(a - 1, b - 1) + YangHui(a - 1, b);
}