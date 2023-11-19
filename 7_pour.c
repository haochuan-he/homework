// 23.11.18
// for homework
// by HHC
#include <stdio.h>
#define min(a, b) a > b ? b : a

int va, vb, vc, a0, b0, c0;
int flag = 0;

int try(int k, int a, int b, int c);
int pour(int k, int a, int b, int c, int mode);

int main()
{
    int k, a, b, c;
    scanf("%d%d%d%d%d%d%d%d%d%d",
          &k, &va, &vb, &vc, &a, &b, &c, &a0, &b0, &c0);
    try(k, a, b, c);

    if (flag > 0)
    {
        printf("Yes");
    }
    else
    {
        printf("No");
    }
    return 0;
}

int try(int k, int a, int b, int c)
{
    // the smallest task
    if (a == a0 && b == b0 && c == c0)
    {
        flag++;
        return 0;
    }
    else if (k == 0 || flag > 0)
    {
        return 0;
    }
    // printf("%d ", tryone++);
    // do it
    return pour(k, a, b, c, 1) +
           pour(k, a, b, c, 2) +
           pour(k, a, b, c, 3) +
           pour(k, a, b, c, 4) +
           pour(k, a, b, c, 5) +
           pour(k, a, b, c, 6);
}
int pour(int k, int a, int b, int c, int mode)
{
    if (flag)
    {
        return 0;
    }
    switch (mode)
    {
    case 1: // a to b

        b = min(a + b, vb);
        a = 0;
        return try(k - 1, a, b, c);
        break;
    case 2: // a to c

        c = min(a + c, vc);
        a = 0;
        return try(k - 1, a, b, c);
        break;
    case 3: // b to c

        c = min(b + c, vc);
        b = 0;
        return try(k - 1, a, b, c);
        break;
    case 4: // c to a

        a = min(a + c, va);
        c = 0;
        return try(k - 1, a, b, c);
        break;
    case 5: // c to b

        b = min(c + b, vb);
        c = 0;
        return try(k - 1, a, b, c);
        break;
    case 6: // b to a

        a = min(a + b, va);
        b = 0;
        return try(k - 1, a, b, c);
        break;
    default:
        printf("--WRONG--");
    }
    return 0;
}