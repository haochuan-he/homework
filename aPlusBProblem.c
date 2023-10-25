// 23.10.25
// for additional problem
// by HHC

#include <stdio.h>
#define MAX 1012
#define max(a, b) (a > b ? a : b)

int main()
{
    int loop = 1;
notend:
    loop--;
    // input
    int a[MAX] = {0}, i = 1, b[MAX] = {0}, j = 1, sum[MAX] = {0};
    for (char ch; (ch = getchar()) != ' '; i++)
    {
        a[i] = ch - '0';
    }
    for (char ch; (ch = getchar()) != EOF; j++)
    {
        if (ch == '\n')
        {
            loop++;
            break;
        }
        b[j] = ch - '0';
    }

    // calculate
    int l = 1;
    for (; l <= max(i, j); l++) // WRONG when the a,b digit not equal
    {
        sum[l] = a[l] + b[l];
    }
    for (; l >= 0; l--)
    {
        if (sum[l] >= 10)
        {
            sum[l] = sum[l] / 10;
            sum[l - 1]++;
        }
    }

    for (int t = (1 - (sum[0] != 0)); t < max(i, j); t++) // to judge the possible carry
    {
        printf("%d", sum[t]);
    }
    if (loop > 0)
    {
        goto notend;
    }

    return 0;
}
/*
// 23.10.25
// for additional problem
// by HHC
#include <stdio.h>
#define MAX 1012
#define min(a, b) (a > b ? b : a)

int main()
{ // test
  // for (int a = 0, b = 0; scanf("%d%d", &a, &b) != EOF;)
  // {
  //     printf("%d\n", a + b);
  // }
    int loop = 1;
notend:
    loop--;
    // input
    int a[MAX + 1] = {0}, i = MAX - 1, b[MAX + 1] = {0}, j = MAX - 1, sum[MAX + 1] = {0};

    for (char ch; (ch = getchar()) != ' '; i--)
    {
        a[i] = ch - '0';
    }
    for (char ch; (ch = getchar()) != EOF; j--)
    {
        if (ch == '\n')
        {
            loop++;
            break;
        }
        b[j] = ch - '0';
    }

    // calculate
    int l = min(i, j);
    for (; l <= MAX; l++)
    {
        sum[l] += a[l] + b[l];
        if (sum[l] >= 10)
        {
            sum[l] /= 10;
            sum[l + 1] = sum[l] % 10;
        }
    }

    for (int t = (MAX - 1) + (sum[t] != 0); t >= min(i, j); t--) // judge if exsist the highest digit carry
    {
        printf("%d", sum[t]);
    }
    printf("\n");

    if (loop > 0)
    {
        goto notend;
    }

    return 0;
}*/
