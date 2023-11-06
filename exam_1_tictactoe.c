// 23.11.5
// for correct
// by HHC

#include <stdio.h>
#define MAX 112

int input(int board[][MAX], int n);
int judge(int num, int board[][MAX], int n, int x);
int judge45(int board[][MAX], int x, int nowrow, int nowcol, int num);

int main()
{
    int t = 0, x = 0;
    scanf("%d%d", &t, &x);
    for (int i = 0; i < t; i++)
    {
        // loop for t times
        int n = 0;
        scanf("%d", &n);

        // initialization
        int board[MAX][MAX];
        for (int i = 0; i < MAX; i++)
        {
            for (int j = 0; j < MAX; j++)
            {
                board[i][j] = 0;
            }
        }

        // input
        input(board, n);

        // judge and output
        if (judge(1, board, n, x) + judge(2, board, n, x) + judge(4, board, n, x) == 1)
        {
            if (judge(1, board, n, x))
            {
                printf("1");
            }
            else if (judge(2, board, n, x))
            {
                printf("2");
            }
            else if (judge(4, board, n, x))
            {
                printf("4");
            }
        }
        else
            printf("draw");

        printf("\n");
    }
    return 0;
}

/***********************************************************
 *
 */
int input(int board[][MAX], int n)
{
    for (int i = 1; i < n + 1; i++)
    {
        for (int j = 1; j < n + 1; j++)
        {
            scanf("%d", &board[i][j]);
        }
    }
    return 0;
}

/**************************************************************
 *
 *
 */
int judge(int num, int board[][MAX], int n, int x)
{
    if (x > n)
    {
        return 0;
    }

    // below:x<=n;
    int cnt = 0;
    // row
    for (int row = 1; row < n + 1; row++)
    {
        for (int col = 1; col < n + 1; col++)
        {
            if (board[row][col] == num)
            {
                cnt++;
            }
            else
            {
                cnt = 0;
            }
            if (cnt == x)
            {
                return 1;
            }
        }
        cnt = 0;
    }
    cnt = 0;

    // col
    for (int col = 1; col < n + 1; col++)
    {
        for (int row = 1; row < n + 1; row++)
        {
            if (board[row][col] == num)
            {
                cnt++;
            }
            else
            {
                cnt = 0;
            }
            if (cnt == x)
            {
                return 1;
            }
        }
        cnt = 0;
    }
    cnt = 0;

    // 45 du
    for (int row = 1; row <= 1 + n - x; row++)
    {
        for (int col = 1; col <= 1 + n - x; col++)
        {
            if (judge45(board, x, row, col, num))
            {
                return 1;
            }
        }
    }
    return 0;
}

/*********************************************************************
 *
 *
 */
int judge45(int board[][MAX], int x, int nowrow, int nowcol, int num)
{
    // right+down
    int flag1 = 1;
    for (int i = nowrow, j = nowcol; i < nowrow + x; i++, j++)
    {
        if (board[i][j] != num)
        {
            flag1 = 0;
            break;
        }
    }
    // left+down
    int flag2 = 1;
    for (int i = nowrow, j = nowcol + x - 1; i < nowrow + x; i++, j--)
    {
        if (board[i][j] != num)
        {
            flag2 = 0;
            break;
        }
    }

    if (flag1 || flag2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}