// 23.10.27
// homework
// by HHC

#include <stdio.h>
#include <stdbool.h>
#define max(a, b) a > b ? a : b

bool Judge(int p, int q, int r, int B);
int transform(int number, int B);
// int input(char into[]);
int maxnum(int num);

int main()
{
    int p = 0, q = 0, r = 0, B = 0;
    // char a[5], b[5], c[5], ch = 0;
    // for (int i = 0; i < 5; i++)
    // {
    //     a[i] = '0';
    //     b[i] = '0';
    //     c[i] = '0';
    // }
    scanf("%d%d%d", &p, &q, &r);
    // if (!input(a) || !input(b) || !input(c))
    // {
    //     printf("0");
    //     return 0;
    // }
    // p = a[4];
    // q = b[4];
    // r = c[4];
    int tmax = max(max(maxnum(p), maxnum(q)), maxnum(r));

    if ((p == 0 || q == 0) && r == 0)
    {
        printf("2");
        return 0;
    }
    if ((p == 0 || q == 0) && r != 0)
    {
        printf("0");
        return 0;
    }

    for (B = 2; B <= 40; B++)
    {
        if (Judge(p, q, r, B) && (tmax < B))
        {
            printf("%d", B);
            break;
        }
    }

    if (B == 41)
    {
        printf("0");
    }

    return 0;
}

int maxnum(int num)
{
    int digit = 0, n = num;
    do
    {
        num /= 10;
        digit++;
    } while (num > 0);
    if (digit == 1)
    {
        return n;
    }
    else
    {
        if ((n / 10) > (n % 10))
        {
            return (n / 10);
        }
        else
        {
            return (n % 10);
        }
    }
}

// int input(char into[])
// {
//     char ch = '0';
//     for (int i = 0; (ch = getchar()) != ' ' || ch != EOF; i++)
//     {
//         into[i] = ch;
//     }

//     if (into[0] == '0' && into[1] != '0')
//     {
//         return 0;
//     }
//     else
//     {
//         into[4] = (into[0] - '0') * 10 + into[1] - '0';
//         return 1;
//     }
// }

bool Judge(int p, int q, int r, int B)
{
    return (transform(p, B) * transform(q, B) == transform(r, B));
}

int transform(int number, int B)
{
    int n = number;
    int digit = 0;
    do
    {
        number /= 10;
        digit++;
    } while (number > 0);

    int ans = 0;
    if (digit == 1)
    {
        ans = n;
    }
    else
    {
        ans = (n / 10) * B + (n % 10);
    }

    return ans;
}

/*
n  int digit = 0;
    do
    {
        n /= 10;
        digit++;
    } while (n >= 10);*/