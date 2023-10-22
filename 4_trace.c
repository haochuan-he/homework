// 23.10.21
// homework
// by HHC

#include <stdio.h>
#define MAX 62

int map[MAX][MAX] = {0};
int xy[2] = {0};
int next_trace(int xy[]);
int main()
{
    int m, n, ans = 0;
    scanf("%d%d%d%d", &n, &m, &xy[0], &xy[1]);
    getchar();
    char ch;
    for (int i = 1; i < 1 + n; i++)
    {
        for (int j = 1; j < 1 + m; j++)
        {
            if ((ch = getchar()) == '#')
            {
                map[i][j] = 1;
                ans++;
            }
        }
        if (n != 1)
        {
            getchar();
        }
    }

    printf("%d\n", ans);
    for (int l = 0; l < ans; l++)
    {
        printf("%d %d\n", xy[0], xy[1]);
        next_trace(xy);
    }

    return 0;
}

int next_trace(int xy[2])
{
    map[xy[0]][xy[1]] = 0;
    if (map[xy[0] + 1][xy[1]] == 1)
    {
        xy[0]++;
    }
    else if (map[xy[0] - 1][xy[1]] == 1)
    {
        xy[0]--;
    }
    else if (map[xy[0]][xy[1] + 1] == 1)
    {
        xy[1]++;
    }
    else if (map[xy[0]][xy[1] - 1] == 1)
    {
        xy[1]--;
    }
    else
    {
        return 1;
    }
    return 0;
}