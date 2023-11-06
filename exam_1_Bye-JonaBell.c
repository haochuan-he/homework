// 23.11.5
// for correct
// by HHC

#include <stdio.h>
#define MAX 1512

int Fire(int fox[], int now, int kill, int total);
int NotFire(int fox[], int now, int kill, int total);
int main()
{ // initializtion
    int n = 0, k = 0, b = 0, l = 0;
    int fox[MAX] = {0};

    scanf("%d%d%d%d", &n, &k, &b, &l);
    for (int i = 1; i <= n; i++)
    {
        fox[i] = l;
    }

    // kill the foxes
    int now = 1;
    for (int i = 0; i < n * l - 1;)
    {
        for (int j = 1; j <= b && (i < (n * l - 1)); j++)
        {
            now = Fire(fox, now, k, n);
            i++;
        }
        now = NotFire(fox, now, k, n);
    }

    // output
    for (int i = 1; i <= n; i++)
    {
        if (fox[i] == 1)
        {
            printf("%d", i);
            break;
        }
    }

    return 0;
}

/********************************************************
 *
 *
 */
int Fire(int fox[], int now, int kill, int total)
{
    int cnt = 0;
    for (; cnt < kill; now++)
    {
        if (now > total)
        {
            now = 1;
        }
        if (fox[now] > 0)
        {
            cnt++;
        }
    }
    // leave:the "now" is the (index+1) to kill
    fox[--now]--;

    // find the next one able to kill,
    // and return its index
    do
    {
        now++;
        if (now > total)
        {
            now = 1;
        }
    } while (fox[now] <= 0);

    return now;
}

/*******************************************************
 *
 *
 */
int NotFire(int fox[], int now, int kill, int total)
{
    int cnt = 0;
    for (; cnt < kill; now++)
    {
        if (now > total)
        {
            now = 1;
        }
        if (fox[now] > 0)
        {
            cnt++;
        }
    }
    // leave:the "now" is the (index+1) to kill
    // fox[--now]--;
    now--;

    // find the next one able to kill,
    // and return its index
    do
    {
        now++;
        if (now > total)
        {
            now = 1;
        }
    } while (fox[now] <= 0);

    return now;
}