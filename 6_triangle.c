// 23.11.13
// for homework
// by HHC

#include <stdio.h>
#include <string.h>
#include <math.h>
#define MAX 4060

char screen[MAX][MAX];
int paint(int n, int row, int col);
int main()
{
    memset(screen, ' ', MAX * MAX); //'0' for easier test
    int n = 0;
    scanf("%d", &n);

    paint(n, pow(2, n), 1);

    for (int row = 1; row <= pow(2, n); row++)
    {
        for (int col = 1; col <= pow(2, n + 1); col++)
        {
            printf("%c", screen[row][col]);
        }
        printf("\n");
    }
    return 0;
}

int paint(int n, int row, int col)
{
    if (n == 1)
    {
        screen[row][col] = screen[row - 1][col + 1] = '/';
        screen[row][col + 1] = screen[row][col + 2] = '_';
        screen[row][col + 3] = screen[row - 1][col + 2] = '\\';
        return 0;
    }

    return paint(n - 1, row + 0, col + 0) +
           paint(n - 1, row - pow(2, n - 1), col + pow(2, n - 1)) +
           paint(n - 1, row + 0, col + pow(2, n));
}