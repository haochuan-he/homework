// 23.10.21
// homework
// by HHC

#include <stdio.h>
#define MAX 9

int num[MAX][MAX] = {0}, flag[MAX][MAX] = {0}, one_flag[MAX] = {0};
int check_small(int trow, int tcol);
int main()
{
    int flag_sum = 0;
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            scanf("%d", &num[i][j]);
            if ((num[i][j] > 9) || (num[i][j] < 1))
            {
                flag[i][0] = -12;
            }
            flag[i][(num[i][j] - 1)]--;
            flag[(num[i][j] - 1)][j]--;
        }
    }

    flag_sum = check_small(0, 0) + check_small(0, 3) + check_small(0, 6) +
               check_small(3, 0) + check_small(3, 3) + check_small(3, 6) +
               check_small(6, 0) + check_small(6, 3) + check_small(6, 6);
    if (flag_sum)
    {
        printf("NO");
        return 0;
    }

    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {

            if (flag[i][j] != -2)
            {
                printf("NO");
                return 0;
            }
        }
    }
    printf("YES");

    return 0;
}

int check_small(int trow, int tcol)
{
    for (int i = 0; i < MAX; i++)
    {
        one_flag[i] = 0;
    }
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            one_flag[num[trow + i][tcol + j] - 1]--;
        }
    }
    for (int i = 0; i < MAX; i++)
    {
        if (one_flag[i] != -1)
        {
            return 1;
        }
    }
    return 0;
}