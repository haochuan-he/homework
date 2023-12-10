// 23.12.10
// for correct
// by HHC

#include <stdio.h>
#include <string.h>
#define flag 100012

int min(int a, int b);
int up(int num, int n, int d, int goal);
int down(int num, int n, int d, int goal);

int main()
{
    // initialize
    int w = 0, n = 0, d = 0;
    scanf("%d%d%d", &w, &n, &d);
    int digit[1012][2];
    memset(digit, 0, 1012 * 2);
    for (int i = 1; i <= w; i++)
    {
        scanf("%d", &digit[i][0]);
    }

    for (int i = 1; i <= w; i++)
    {
        digit[i][1] = up(digit[i][0], n, d, digit[w - i + 1][0]);
        // NO WAY
        if (digit[i][1] == flag)
        {
            printf("Impossible");
            return 0;
        }
    }
    int sum = 0;
    for (int i = 1; i <= (w / 2); i++)
    {
        sum += min(digit[i][1], digit[w - i + 1][1]);
    }

    // for (int i = 1; i <= (w / 2); i++)
    // {
    //     digit[i][1] = min(up(digit[i][0], n, d, digit[w - i + 1][0]),
    //                       down(digit[i][0], n, d, digit[w - i + 1][0]));
    //     // NO WAY
    //     if (digit[i][1] == flag)
    //     {
    //         printf("Impossible");
    //         return 0;
    //     }
    // }
    // int sum = 0;
    // for (int i = 1; i <= (w / 2); i++)
    // {
    //     sum += digit[i][1];
    // }
    printf("%d", sum);

    return 0;
}
int min(int a, int b)
{
    return a > b ? b : a;
}
int up(int num, int n, int d, int goal)
{

    int i = num, cnt = 0, tem = d - 1;

    for (; i != goal && (cnt <= n);)
    {
        i = (i + tem) % n + 1; // better method takes less time,
        // i += d;
        // if (i > n)
        // {
        //     i = i - n;
        // }
        if (i == num)
        {
            break;
        }
        cnt++;
    }
    if (i > n)
    {
        i = i - n;
    }
    // printf("up%d--%d\n", cnt, num);
    if (i == goal)
    {
        return cnt;
    }
    else
    {
        return flag;
    }
}
int down(int num, int n, int d, int goal)
{
    int i = num, cnt = 0, tem = n - d - 1;

    for (; i != goal && (cnt <= 2 * n * n);)
    {
        // i = (i + tem) % n + 1;
        i -= d;
        if (i < 1)
        {
            i = n + i;
        }
        if (i == num)
        {
            break;
        }
        cnt++;
    }
    if (i < 1)
    {
        i = n + i;
    }
    // printf("bakc %d--%d\n", cnt, num);
    if (i == goal)
    {
        return cnt;
    }
    else
    {
        return flag;
    }
}