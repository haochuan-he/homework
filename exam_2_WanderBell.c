#include <stdio.h>
#include <string.h>
#define MAX 3012
int r, c;
char map[MAX][MAX];

int check(int row, int col);

int main()
{

    memset(map, '.', MAX * MAX);

    scanf("%d%d", &r, &c);
    getchar();
    for (int row = 0; row < r; row++)
    {
        for (int col = 0; col < c; col++)
        {
            scanf("%c", &map[row][col]);
        }
        getchar();
    }

    int cnt = 0;
    for (int row = 0; row < r; row++)
    {
        for (int col = 0; col < c; col++)
        {
            if (map[row][col] != '.')
            {
                int tem = check(row, col);
                if (tem != -1)
                {
                    cnt += tem;
                }
                else
                {
                    printf("%d", -1);
                    return 0;
                }
            }
        }
    }

    printf("%d", cnt);

    // for (int row = 0; row < r; row++)
    // {
    //     for (int col = 0; col < c; col++)
    //     {
    //         printf("%c", map[row][col]);
    //     }
    //     putchar('\n');
    // }
    return 0;
}

int check(int row, int col)
{
    // check no arrow
    int no = 1;
    for (int j = 0; j < c; j++)
    {
        if (map[row][j] != '.' && j != col)
        {
            no = 0;
            break;
        }
    }
    for (int j = 0; j < r; j++)
    {
        if (map[j][col] != '.' && j != row)
        {
            no = 0;
            break;
        }
    }
    if (no == 1)
    {
        return -1;
    }
    // calculate the step
    switch (map[row][col])
    {
    case 'R':
        for (int i = col + 1; i < c; i++)
        {
            if (map[row][i] != '.')
            {
                return 0;
            }
        }
        return 1;
        break;
    case 'L':
        for (int i = col - 1; i >= 0; i--)
        {
            if (map[row][i] != '.')
            {
                return 0;
            }
        }
        return 1;
        break;
    case 'U':
        for (int i = row - 1; i >= 0; i--)
        {
            if (map[i][col] != '.')
            {
                return 0;
            }
        }
        return 1;
        break;
    case 'D':
        for (int i = row + 1; i < r; i++)
        {
            if (map[i][col] != '.')
            {
                return 0;
            }
        }
        return 1;
        break;
    }
}