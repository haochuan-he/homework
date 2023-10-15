/*
// 23.10.15 11:43
// homework
// by HHC

#include <stdio.h>

int main()
{
    int n = 0;
    scanf("%d", &n);

    return 0;
}
*/

// 23.10.14
// homework
// by HHC

#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

#define MAX 25
#define MAXSIZE 10012

int main()
{
    int n = 0;
    scanf("%d", &n);
    getchar();

    char in[MAX];
    int out[MAXSIZE], is_nag = 0;
    char ans[MAX][MAX];

    int w = -1;

    for (int i = 0; i < n; i++)
    {
        out[i] = 0;
        is_nag = 0;
        fgets(in, MAX, stdin);
        in[strcspn(in, "\n")] = '\0';

        // legal test and transform char to int
        if (in[0] == '-')
        {
            is_nag = 1;
        }
        for (int j = 0; j < strlen(in); j++)
        {
            if (is_nag == 1)
            {
                is_nag++;
                continue;
            }
            if (isdigit(in[j]))
            {
                out[i] = out[i] * 10 + (in[j] - '0');
            }
            else
            {
                out[i] = INT_MIN; // flag
                break;
            }
        }
        // if (is_nag)
        // {
        //     out[i] *= -1;
        // }

        // transform the 10 to 3 digit

        if (out[i] != INT_MIN)
        {
            int three[MAX] = {0}, j = 0;

            do
            {
                three[j] = out[i] % 3; // j min,digit right;max  meaningflu index is j-1(when leave the loop)
                out[i] /= 3;
                j++;

            } while (out[i] != 0);

            ans[i][j] = '\n';

            w = -1;

            for (int v = 0; v < j; v++)
            {
                w++;

                if (three[w] == 0)
                {
                    ans[i][w] = '0';
                }
                else if (three[w] == 1)
                {
                    ans[i][w] = '1';
                }
                else if (three[w] == 2)
                {
                    ans[i][w] = 'Z';
                    three[w + 1] += 1;
                    v--;
                    continue;
                }
                else
                {
                    ans[i][w] = '0';
                    three[w + 1] += 1;
                    v--;
                    continue;
                }
            }
            ans[i][w + 1] = '\n';

            if (is_nag) // for nagtive numbers only
            {
                for (int k = 0; k < w; k++)
                {
                    if (ans[i][k] == 'Z')
                    {
                        ans[i][k] = '1';
                    }
                    else if (ans[i][k] == '1')
                    {
                        ans[i][k] = 'Z';
                    }
                }
            }
        }
        else
        {
            ans[i][0] = '\0'; // flag
        }
    }

    // output
    for (int i = 0; i < n; i++)
    {
        if (ans[i][0] == '\0')
        {
            printf("Radix Error\n");
        }
        else if (ans[i][0] == '0' && ans[i][1] == '\n')
        {
            printf("0\n");
        }
        else
        {
            int cnt = 0, have_pri = 0;
            for (cnt = 0; ans[i][cnt] != '\n'; cnt++)
            {
                ;
            }
            for (int j = cnt; j >= 0; j--)
            {
                if (ans[i][j] != '0' && ans[i][j] != '\n')
                {
                    have_pri = 1;
                }
                if (have_pri == 0)
                {
                    if (ans[i][j] == '0')
                    {
                        continue;
                    }
                }
                else
                    (printf("%c", ans[i][j]));
            }
            printf("\n");
        }
    }

    // // debug:legal part
    // for (int m = 0; m < n; m++)
    // {
    //     printf("%d\n", out[m]);

    return 0;
}
