// 23.10.15 21:30
// homework
// by HHC

#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

#define MAXSIZE 112 // have to change betweem my PC and OJ
#define MAX 25
// #define ENOUGH 5

int input(int total, char in[][MAX]);
int legal_test(int total, char in[][MAX], int legal[][MAX]);
int transform_three(int total, int three[][MAX], int legal[][MAX]);
int transform_ternary(int total, int three[][MAX], char out[MAXSIZE][MAX]);

int main()
{
    int total = 0;
    scanf("%d", &total);
    getchar();

    char original[MAXSIZE][MAX], out[MAXSIZE][MAX];
    int legal[MAXSIZE][MAX], three[MAXSIZE][MAX];

    input(total, original);

    legal_test(total, original, legal);

    transform_three(total, three, legal);

    transform_ternary(total, three, out);

    // output
    for (int i = 0; i < total; i++)
    {
        int pass_min = 0;
        if (out[i][0] == '\0')
        {
            printf("Radix Error");
        }
        for (int j = MAX - 1; j > 0; j--)
        {
            if (out[i][j] == '1' || out[i][j] == 'Z')
            {
                pass_min = 1;
            }
            if (pass_min == 1)
            {
                printf("%c", out[i][j]);
            }
            if (pass_min == 0 && j == 1 && out[i][j] == '0')
            {
                printf("0");
            }
        }
        printf("\n");
    }

    // // test
    // for (int i = 0; i < total; i++)
    // {
    //     printf("flag=%d reverse%d%d%d%d___", three[i][0], three[i][1], three[i][2], three[i][3], three[i][4]);
    //     for (int j = 0; original[i][j] != '\0' && j < MAX; j++)
    //     {
    //         printf("char=%c ", original[i][j]);
    //     }
    //     printf("\n");
    // }

    return 0;
}

/******************************************************************
 *   input(int,char[][]):to put all the stastic into
 *       two-dimensional array;
 *   return 0 .
 *
 * TESTED
 */
int input(int total, char in[MAXSIZE][MAX])
{
    for (int i = 0; i < total; i++)
    {
        fgets(in[i], MAX, stdin);
        in[i][strcspn(in[i], "\n")] = '\0';
    }
    return 0;
}

/*******************************************************************
 *  legal_test(int total,char in[][],legal[][MAX]):
 * to test if the legal is legal ;
 * if it is illgal,legal[][0]=INT_MIN;
 * return 0.
 *
 * TESTED
 */
int legal_test(int total, char in[][MAX], int legal[][MAX])
{
    for (int i = 0; i < total; i++)
    {
        for (int j = 0; (j < MAX) && in[i][j] != '\0'; j++)
        {
            if (!('0' <= in[i][j] && in[i][j] <= '9') && in[i][j] != '-')
            {
                legal[i][0] = INT_MIN;
                break;
            }
        }
        if (legal[i][0] != INT_MIN)
        {
            if (in[i][0] == '-')
            {
                legal[i][0] = 0;
                for (int j = 1; in[i][j] != '\0'; j++)
                {
                    legal[i][0] = legal[i][0] * 10 + (in[i][j] - '0');
                }
                legal[i][0] *= -1;
            }
            else
            {
                legal[i][0] = 0;
                for (int j = 0; in[i][j] != '\0'; j++)
                {
                    legal[i][0] = legal[i][0] * 10 + (in[i][j] - '0');
                }
            }
        }
    }
    return 0;
}

/***************************************************************************
 * int transform_three(int total, int three[][MAX], int legal[][MAX]):
 * transform the digit in 10 to digit in 3,put them into three "one by one":
 * the lower digits' index is smaller(begin form 1);
 * index 0: 1 for positive; 0 for negtive
 *
 * return 0.
 *
 * TESTED
 */
int transform_three(int total, int three[][MAX], int legal[MAXSIZE][MAX])
{
    for (int i = 0; i < total; i++)
    {
        if (legal[i][0] != INT_MIN && legal[i][0] > 0) // positive
        {
            int j = 0;
            three[i][0] = 1;
            for (j = 1; legal[i][0] != 0; j++)
            {
                three[i][j] = legal[i][0] % 3;
                three[i][j + 2] = INT_MIN; // flag
                legal[i][0] /= 3;
            }
        }
        else if (legal[i][0] != INT_MIN && legal[i][0] < 0) // negative
        {
            int j = 0;
            three[i][0] = 0;
            legal[i][0] *= -1;
            for (j = 1; legal[i][0] != 0; j++)
            {
                three[i][j] = legal[i][0] % 3;
                three[i][j + 2] = INT_MIN; // flag
                legal[i][0] /= 3;
            }
        }
        else if (legal[i][0] == INT_MIN)
        {
            three[i][0] = INT_MIN;
        }
    }

    return 0;
}

/********************************************************************************
 * int transform_ternary(int total, int three[][MAX], char out[MAXSIZE][MAX]):
 * transform the traditional digit 3 to Z_0_1 form,putinto char out[][](begin from 1);
 *
 * return 0.
 *
 *
 */
int transform_ternary(int total, int three[MAXSIZE][MAX], char out[MAXSIZE][MAX])
{
    for (int i = 0; i < total; i++)
    {
        out[i][0] = 1; // flag:skip
        if (three[i][0] == INT_MIN)
        {
            out[i][0] = '\0';
        }
        else
        {
            for (int j = 1; three[i][j] != INT_MIN && j < MAX; j++)
            {
                if (three[i][j] == 1 || three[i][j] == 0)
                {
                    out[i][j] = three[i][j] + '0';
                }
                else if (three[i][j] == 2)
                {
                    out[i][j] = 'Z';
                    if (three[i][j + 1] == INT_MIN)
                    {
                        three[i][j + 1] = 1;
                        three[i][j + 2] = INT_MIN;
                    }
                    else
                    {
                        three[i][j + 1] += 1;
                    }
                }
                else if (three[i][j] == 3)
                {
                    out[i][j] = '0';
                    if (three[i][j + 1] == INT_MIN)
                    {
                        three[i][j + 1] = 1;
                        three[i][j + 2] = INT_MIN;
                    }
                    else
                    {
                        three[i][j + 1] += 1;
                    } // digit space is ok;maybe 0...
                }
            }
            if (three[i][0] == 0)
            {

                for (int j = 1; (three[i][j] != INT_MIN) && (j < MAX); j++) // bugs:condition failed !!!?
                {

                    if (out[i][j] == '1')
                    {
                        out[i][j] = 'Z';
                    }
                    else if (out[i][j] == 'Z')
                    {
                        out[i][j] = '1';
                    }
                }
            }
        }
    }

    return 0;
}


/*

//failed:unknow bugs will occur when INT_MAX or INT_MIN+1

// 23.10.14
// homework
// by HHC

// 2147483647
//-2147483646

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
    char ans[MAXSIZE][MAX];

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
                three[j] = out[i] % 3; // j min,digit right;max  meaningflu index is j-1(when leave the loop);total digit ==j
                out[i] /= 3;
                j++;

            } while (out[i] != 0);

            ans[i][j] = '\n';

            for (w = 0; w < 1 + j; w++) // plus:j+1;normal:j
            {

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

                    continue;
                }
                else // three[w]==3
                {
                    ans[i][w] = '0';
                    three[w + 1] += 1;

                    continue;
                }
            }
            // leave the loop:w eaqual the total(-1)of three
            ans[i][w + 1] = '\n';

            if (is_nag) // for nagtive numbers only
            {
                for (int k = 0; k <= w; k++)
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
*/