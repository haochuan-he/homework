// 23.10.21
// homework
// by HHC

#include <stdio.h>
#define MAX 1012

int n = 0, old_life[MAX] = {0}, new_life[MAX] = {0};

int no_life(int now);
int is_life(int now);
int main()
{
    // input
    scanf("%d", &n);
    getchar();
    char ch;
    int total = 0;
    for (int i = 3; i < MAX; i++)
    {
        if ((ch = getchar()) != '\n')
        {
            total++;
            if (ch == 'A')
            {
                old_life[i] = 1;
            }
            else if (ch == 'B')
            {
                old_life[i] = -1;
            }
        }
        else
        {
            break;
        }
    }
    // loop
    for (int l = 0; l < n; l++)
    {
        for (int i = 3; i < 3 + total; i++)
        {
            if (old_life[i] == 0)
            {
                new_life[i] = no_life(i);
            }
            else
            {
                new_life[i] = is_life(i);
            }
        }
        for (int i = 3; i < 3 + total; i++)
        {
            old_life[i] = new_life[i];
        }
    }

    // out put
    for (int i = 3; i < 3 + total; i++)
    {
        if (old_life[i] == 1)
        {
            printf("A");
        }
        else if (old_life[i] == -1)
        {
            printf("B");
        }
        else
        {
            printf(".");
        }
    }

    // // test
    // for (int i = 0; i < 20; i++)
    // {
    //     printf("%d", old_life[i]);
    // }

    return 0;
}
//
//
//
//
//
int is_life(int now)
{
    int iam = old_life[now], cnt = 0;
    for (int i = now - 3; i <= now + 3; i++)
    {
        if (old_life[i] == (-1) * iam) // transform to enemy:*(-1),not'!='(due to 0)
        {
            return 0;
        }
        else if (old_life[i] == iam)
        {
            cnt++;
        }
    }
    cnt--; // i = now
    if (cnt <= 1 || cnt >= 5)
    {
        return 0;
    }
    else
    {

        return iam;
    }
}

int no_life(int now)
{
    int iam = 0, i = -3, cnt = 0;
    for (; old_life[now + i] == 0 && i <= 3; i++)
        ;
    if (i == 6)
    {
        return 0;
    }
    else
    {
        iam = old_life[now + i];

        for (; i <= 3; i++)
        {
            if (old_life[now + i] == (-1) * iam)
            {
                return 0;
            }
            else if (old_life[now + i] == iam)
            {
                cnt++;
            }
        }
    }
    if (2 <= cnt && cnt <= 4)
    {
        return iam;
    }
    else
    {
        return 0;
    }
}