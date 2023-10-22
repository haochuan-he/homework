// 23.10.21
// homework
// by HHC

#include <stdio.h>
#define MAX 2012 // change2012 on OJ

int flag(int all[MAX][MAX], int row, int col);
int main()
{
    int m, n, all[MAX][MAX] = {0};
    scanf("%d%d", &m, &n);
    getchar();
    for (int i = 1; i < n + 1; i++)
    {
        all[0][i] = (getchar() - '0');
    }

    for (int row = 1; row < m; row++)
    {
        for (int col = 1; col < n + 1; col++)
        {
            all[row][col] = flag(all, row, col);
        }
    }
    for (int row = 1; row < m; row++)
    {
        for (int col = 1; col < n + 1; col++)
        {
            printf("%d", all[row][col]);
        }
        printf("\n");
    }

    return 0;
}

int flag(int all[MAX][MAX], int row, int col)
{
    int sum = 0;
    sum = all[row - 1][col - 1] + all[row - 1][col] + all[row - 1][col + 1];
    if (sum == 3 || sum == 0 || (all[row - 1][col - 1] == 1 && all[row - 1][col] == 0 && all[row - 1][col + 1] == 0))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}