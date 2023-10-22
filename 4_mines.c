// 23.10.21
// homework
// by HHC
#include <stdio.h>
#define MAX 112

int mine[MAX][MAX][2] = {0};
int check(int row, int col);
int main()
{
    int n = 0;
    scanf("%d", &n);
    getchar();
    for (int i = 1; i < n + 1; i++)
    {
        for (int j = 1; j < n + 1; j++)
        {
            if (getchar() == '*')
            {
                mine[i][j][1] = 1;
            }
        }
        getchar();
    }

    int flag = 0;
    for (int i = 1; i < n + 1; i++)
    {
        for (int j = 1; j < n + 1; j++)
        {
            flag = 0;
            if ((flag = check(i, j)) != -1)
            {
                printf("%d", flag);
            }
            else
            {
                printf("*");
            }
        }
        printf("\n");
    }
    return 0;
}

int check(int row, int col)
{
    int sum = 0;
    if (mine[row][col][1] == 0)
    {
        sum = mine[row - 1][col - 1][1] + mine[row - 1][col][1] + mine[row - 1][col + 1][1] +
              mine[row][col - 1][1] + mine[row][col + 1][1] +
              mine[row + 1][col - 1][1] + mine[row + 1][col][1] + mine[row + 1][col + 1][1];
    }
    else
    {
        sum = -1;
    }
    return sum;
}