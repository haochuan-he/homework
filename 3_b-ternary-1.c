// 23.10.14
// homewoek
// by HHC

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#define MAX 2000

int main()
{
    int n = 0;
    scanf("%d", &n);
    getchar();
    char in[MAX];
    int out[n];
    // for (int i = 0; i < n; i++)
    // {
    //     out[i] = 0;
    // }

    for (int m = 0; m < n; m++)
    {
        fgets(in, MAX, stdin);
        in[strcspn(in, "\n")] = '\0';
        // // test
        // for (int t = 0; t < strlen(in); t++)
        // {
        //     printf("%c", in[t]);
        // }

        // legal test
        for (int i = 0; i < strlen(in); i++)
        {
            if (in[i] != '0' && in[i] != '1' && in[i] != 'Z')
            {
                if (in[i] != '\0')
                {
                    out[m] = INT_MIN; // flag
                }
                break;
            }
        }

        // transition and calculate
        if (out[m] != INT_MIN)
        {
            int sum = 0, cnt = 0;
            for (int k = strlen(in) - 1, cnt = 0; k >= 0; k--)
            {
                if (in[k] == '1')
                {
                    sum += pow(3, cnt);
                }
                else if (in[k] == 'Z')
                {
                    sum -= pow(3, cnt);
                }
                cnt++;
            }
            out[m] = sum;
        }
    }

    // output
    for (int i = 0; i < n; i++)
    {
        if (out[i] == INT_MIN)
        {
            printf("Radix Error\n");
        }
        else
        {
            printf("%d\n", out[i]);
        }
    }
    return 0;
}
/*
// 23.10.14 19:00
// homework
// by HHC

#include <stdio.h>
#define MAX 200

int main()
{
    int n = 0, sum;
    scanf("%d", &n);
    getchar();

    int out[n], tem[n];
    for (int i = 0; i < n; i++)
    {
        out[i] = 0;
        tem[i] = 0;
    }

    for (int i = 0; i < n;)
    {
        int j = 0;
        char num[MAX] = {0};
        sum = 0;

        for (j = 0; j < MAX; j++)
        {
            num[j] = getchar();
            if (num[j] == '\n')
            {
                break;
            }
            else if (num[j] == 'Z')
            {
                tem[j] = -1;
            }
            else if (num[j] == '0')
            {
                tem[j] = 0;
            }
            else if (num[j] == '1')
            {
                tem[j] = 1;
            }
            else
            {
                sum = -12; // flag
                break;
            }
            sum = (sum + tem[j]) * 3;
        }

        out[i] = sum;
        i++;
    }

    for (int i = 0; i < n; i++)
    {
        if (out[i] == -12)
        {
            printf("Radix Error\n");
        }
        else
        {
            printf("%d\n", out[i] / 3);
        }
    }

    return 0;
}
*/

/*wrong:do not know how to use two-dimensional array
// 23.10.14
// homework
// by HHC

#include <stdio.h>
#define MAX 20

int main()
{
    int n = 0;
    scanf("%d", &n);
    getchar(); // deal with enter
    char num[n][MAX];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            num[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++)
    {
        fgets(num[i], MAX, stdin);
    }

    // // test

    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < MAX; j++)
    //     {
    //         printf("%c", num[i][j]);
    //         printf(" j=%d ", j);
    //     }
    // }

    // test the illegal input

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            if (num[i][j] == '\0')
            {
                break;
            }
            if (num[i][j] == 'Z')
            {
                num[i][j] = -1;
            }
            if (num[i][j] != '1' && num[i][j] != 'Z' && num[i][j] != '0')
            {
                num[i][0] = '*'; // flag
                break;
            }
        }
    }

    // transit
    for (int i = 0; i < n; i++)
    {
        int sum = num[i][0];
        if (num[i][0] == -1)
        {
            continue;
        }
        for (int j = 0; j < MAX; j++)
        {
            if (num[i][j] == '\0')
            {
                break;
            }
            sum = (sum + num[i][j]) * 3;
        }
        num[i][0] = sum / 3;
    }

    // output
    for (int i = 0; i < n; i++)
    {

        for (int j = 0; j < MAX; j++)
        {
            if (num[i][j] == '\0')
            {
                break;
            }
            if (num[i][0] == '*')
            {
                printf("Radix Error\n");
                break;
            }
            else
            {
                printf("%d\n", num[i][0]);
                break;
            }
        }
    }

    return 0;
}
*/