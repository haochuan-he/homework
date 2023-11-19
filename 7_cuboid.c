// 23.11.19
// for homework
// by HHC

#include <stdio.h>
#include <string.h>
#define MAX 200

int map[MAX][MAX];

int draw(int a, int b, int c);
int line(int a, int row, int col);
int line1(int a, int row, int col);
int line2(int a, int row, int col);
int downline(int c, int row, int col);
int downline2(int c, int row, int col);

int main()
{
    int t = 0;
    scanf("%d", &t);
    // loop for t times
    for (int i = 0; i < t; i++)
    {
        memset(map, ' ', MAX * MAX);
        int a = 0, b = 0, c = 0;
        scanf("%d%d%d", &a, &b, &c);
        draw(a, b, c);

        for (int row = 1; row <= 2 * b + 2 * c + 1; row++)
        {
            for (int col = 0; col <= 2 * a + 2 * b + 1; col++)
            {
                printf("%c", map[row][col]);
            }
            printf("\n");
        }
    }

    return 0;
}

int draw(int a, int b, int c)
{ // the up
    for (int space = 2 * b; space > 0; space--)
    {
        if (space % 2 == 0)
        {
            line(a, 2 * b - space + 1, space);
        }
        else
        {
            line1(a, 2 * b - space + 1, space);
        }
    }
    // the front
    for (int i = 0; i < 2 * c + 1; i++)
    {
        if (i % 2 == 0)
        {
            line(a, 2 * b + 1 + i, 0);
        }
        else
        {
            line2(a, 2 * b + 1 + i, 0);
        }
    }
    // the right
    for (int i = 0; i < 2 * b + 1; i++)
    {
        if (i % 2 == 0)
        {
            downline(c, 2 * b + 1 - i, 2 * a + i);
        }
        else
        {
            downline2(c, 2 * b + 1 - i, 2 * a + i);
        }
    }
}

int line(int a, int row, int col) // +-+-+-+-+-+-+
{
    map[row][col] = '+';
    for (int i = 0; i < a; i++)
    {
        map[row][++col] = '-';
        map[row][++col] = '+';
    }
    return 0;
}
int line1(int a, int row, int col) // / / / / / / /
{
    map[row][col] = '/';
    for (int i = 0; i < a; i++)
    {
        map[row][++col] = ' ';
        map[row][++col] = '/';
    }
    return 0;
}
int line2(int a, int row, int col) // | | | | | | |
{
    map[row][col] = '|';
    for (int i = 0; i < a; i++)
    {
        map[row][++col] = ' ';
        map[row][++col] = '|';
    }
    return 0;
}
int downline(int c, int row, int col)
{
    map[row][col] = '+';
    for (int i = 0; i < c; i++)
    {
        map[++row][col] = '|';
        map[++row][col] = '+';
    }
}

int downline2(int c, int row, int col)
{
    map[row][col] = '/';
    for (int i = 0; i < c; i++)
    {
        map[++row][col] = ' ';
        map[++row][col] = '/';
    }
}