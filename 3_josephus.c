/*failed;

// 23.10.15
// homework
// by HHC

#include <stdio.h>

int main()
{
    int total = 0, kill = 0;
    scanf("%d%d", &total, &kill);

    int people[total];

    for (int i = 0; i < total; i++)
    {
        people[i] = 1;
    }
    int i = 0;
    for (int k = 0; k < total - 1; k++)
    {
        int cnt = 0;

        for (; cnt < kill; i++)
        {
            if (i == total)
            {
                i = 0;
            }
            if (people[i] == 0)
            {

                continue;
            }
            else
            {
                cnt++;
            }
        }
        people[i] = 0;
        i++;
    }

    for (int i = 0; i < total; i++)
    {
        if (people[i] == 1)
        {
            printf("%d", i + 1);
            break;
        }
    }

    return 0;
}*/

// version 1.0  time limit exceed
// success:my function must return 0;
//  23.10.15 16:10
//  homework
//  by HHC

#include <stdio.h>
#define MAX 512
int die(int, int, int[]);
int main()
{
    int total = 0, kill = 0;
    scanf("%d%d", &total, &kill);

    int people[MAX];
    for (int i = 0; i < total; i++)
    {
        people[i] = i + 1;
    }

    die(total, kill, people);

    return 0;
}

int die(int total, int kill, int people[MAX])
{

    if (total == 1)
    {
        printf("%d", people[0]);
        return 0;
    }

    int k = kill;
    while (k - total > 0)
    {
        k -= total;
    }

    people[k - 1] = -1;

    int in[MAX];

    for (int i = 0; i < total - 1; i++, k++)
    {
        if (k == total)
        {
            k = 0;
        }

        in[i] = people[k];
    }

    die(total - 1, kill, in);
}

/*
// 23.10.14
// homework
// by HHC

#include <stdio.h>

int die(int n, int k, int peopel[], int last);

int main()
{
    int n = 0, k = 0, last = 0, ans = -1;
    scanf("%d%d", &n, &k);

    int people[n + 1];
    for (int i = 1; i < 1 + n; i++)
    {
        people[i] = i; // flag: -1:die
    }

    ans = die(n, k, people, last);
    printf("%d", ans);
    return 0;
}

int die(int n, int k, int people[n], int last)
{
    int max = n + 1, min = 1, ans = 0;
    for (; people[max] == -1; max--)
        ;
    for (; people[min] == -1; min++)
        ;

    if (max == min)
    {
        return max;
    }

    int cnt = 0, now = last + 1;
    while (cnt < k - 1)
    {
        if (now >= max)
        {
            now = min - 1;
            cnt++;
        }
        else
        {
            if (people[now] != -1)
            {
                cnt++;
                now++;
            }
            else
            {
                now++;
            }
        }
    }
    people[now] = -1;
    last = now;
    ans = die(n - 1, k, people, last);
    return ans;
}
*/