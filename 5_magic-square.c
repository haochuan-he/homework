// 23.10.27
// homework
// by HHC
#include <stdio.h>
#define MAX 10 // must change to 1012 on OJ

int PutInto(int suqare[][MAX], int now[], int number, int total);

int main()
{
    int n = 0, suqare[MAX][MAX] = {0}, now[2] = {0}; // there begin form 1
    scanf("%d", &n);

    now[0] = (n + 1) / 2;
    now[1] = 1;

    for (int i = 1; i <= n * n; i++)
    {
        PutInto(suqare, now, i, n);
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            printf("%d ", suqare[i][j]);
        }
        printf("\n");
    }

    return 0;
}

int PutInto(int suqare[][MAX], int now[], int number, int total)
{
    int next[2] = {0};

    // move to the right-up position
    if (now[0] == 1)
    {
        next[0] = total;
    }
    else
    {
        next[0] = now[0] - 1;
    }

    if (now[1] == total)
    {
        next[1] = 1;
    }
    else
    {
        next[1] = now[1] + 1;
    }

    // fill the number
    if (suqare[next[0]][next[1]] == 0)
    {
        suqare[next[0]][next[1]] = number;
        now[0] = next[0];
        now[1] = next[1];
        return 0;
    }
    else
    {
        // move down to fill the number
        if (now[0] == total)
        {
            suqare[1][now[1]] = number;
            now[0] = 1;
            return 0;
        }
        else
        {
            suqare[now[0] + 1][now[1]] = number;
            now[0]++;
            return 0;
        }
    }
}