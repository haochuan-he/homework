// 23.11.19
// for homework
// by HHC

#include <stdio.h>
#include <string.h>
#include <limits.h>
#define MAX 200 // 732
#define SPACE 60

int map[MAX][MAX][2];

int value(int row, int col, int d);
int next_value(int row, int col, int d);
int main()
{ // initialization
    int n, m, d;
    scanf("%d%d%d", &n, &m, &d);
    for (int i = SPACE; i < n + SPACE; i++)
    {
        for (int j = SPACE; j < m + SPACE; j++)
        {
            scanf("%d", &map[i][j][0]);
        }
    }
    // calculate the sum value
    for (int i = SPACE; i < n + SPACE; i++)
    {
        for (int j = SPACE; j < m + SPACE; j++)
        {
            if (j == SPACE)
            {
                value(i, j, d);
            }
            else
            {
                next_value(i, j, d);
            }
        }
    }
    // find the max value and putout
    int max_value = INT_MIN, ans[360000][2] = {0}, cnt = 0;
    for (int i = SPACE; i < n + SPACE; i++)
    {
        for (int j = SPACE; j < m + SPACE; j++)
        {
            if (max_value < map[i][j][1])
            {
                memset(ans, 0, 360000 * 2);
                cnt = 1;
                max_value = map[i][j][1];
                ans[cnt][0] = i;
                ans[cnt][1] = j;
            }
            else if (max_value == map[i][j][1])
            {
                ans[++cnt][0] = i;
                ans[cnt][1] = j;
            }
        }
    }

    printf("%d %d\n", max_value, cnt);
    for (int i = 1; i <= cnt; i++)
    {
        printf("%d %d\n", ans[i][0] - SPACE + 1, ans[i][1] - SPACE + 1);
    }

    return 0;
}

int value(int row, int col, int d)
{
    int sum = 0;
    for (int cnt = 0; cnt < d; cnt++)
    {
        for (int tcol = col - cnt; tcol <= col + cnt; tcol++)
        {
            sum += map[row + d - cnt][tcol][0];
            sum += map[row - d + cnt][tcol][0];
        }
    }
    for (int tcol = col - d; tcol <= col + d; tcol++)
    {
        sum += map[row][tcol][0];
    }
    map[row][col][1] = sum;
    return sum;
}

int next_value(int row, int col, int d)
{
    int sum = map[row][col - 1][1], diff = 0;
    for (int i = 0; i < d; i++)
    {
        diff += map[row - d + i][col + i][0] - map[row - d + i][col - 1 - i][0];
        diff += map[row + d - i][col + i][0] - map[row + d - i][col - 1 - i][0];
    }
    diff += map[row][col + d][0] - map[row][col - d - 1][0];
    map[row][col][1] = map[row][col - 1][1] + diff;
    return 0;
}