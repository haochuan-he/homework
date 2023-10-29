// 23.10.27
// homework
//  by HHC

#include <stdio.h>
#define MAX 2012

int After(int line[], int n);

int main()
{
    // input
    int n = 0, line[MAX] = {0};
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &line[i]);
    }

    // find m
    // int len_after[MAX] = {0};
    // for (int i = n; i >0; i--)
    // {
    //     len_after[i] = After(i, line, n);
    // }
    // int m = 0;
    // for (int i = 0; i <= n; i++)
    // {
    //     if (m < len_after[i])
    //     {
    //         m = len_after[i];
    //     }
    // }
    int m = 0;
    m = After(line, n);
    // printf("m=%d\n", m);

    // exchange
    int pk = line[n - m], the_min = line[n - m + 1], the_index = n - m + 1;
    for (int i = n - m + 1; i <= n; i++)
    {
        if (pk < line[i] && the_min > line[i])
        {
            the_min = line[i];
            the_index = i;
        }
    }
    line[the_index] = line[n - m];
    line[n - m] = the_min;

    // print
    for (int i = 1; i <= n - m; i++)
    {
        printf("%d ", line[i]);
    }
    for (int i = n; i > n - m; i--)
    {
        printf("%d ", line[i]);
    }

    // printf("%d", m);
    return 0;
}
/*********************************************************
 * After:count the lenth of decent line begin with line[now]
 *
 * TESTED
 */
int After(int line[], int n)
{
    int cnt = 1;
    for (int i = n; line[i - 1] > line[i] && (i - 1) >= 1; i--)
    {
        cnt++;
    }
    return cnt;
}

/*
// 23.10.27
// homework
// by HHC

#include <stdio.h>
#define MAX 2012

int After(int nwo, int line[], int n);

int main()
{
    int n = 0, line[MAX] = {0}, after[MAX] = {0}; // begin form 1
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &line[i]);
    }

    for (int i = 0; i < n; i++)
    {
        after[i] = After(i, line, n);
    }
    // find the 'm'
    int max_index = 0;
    for (int i = 0; i < n; i++)
    {
        if (after[i] > after[max_index])
        {
            max_index = i;
        }
    }
    int m = 0, pk = 0;
    if (max_index != 1)
    {
        m = after[max_index];
        pk = line[max_index - 1];
    }
    else
    {
        pk = line[1];
        m = after[max_index];
    }

    // find the min of larger in the decent line
    int minone_index = 0;
    for (int i = max_index; i <= (m + max_index); i++)
    {
        if (line[i] > pk && line[i] < line[minone_index])
        {
            minone_index = i;
        }
    }
    // exchange
    int temp = pk;
    line[minone_index] = pk;
    line[max_index - 1] = temp;

    // printf && reverse
    for (int i = 1; i <= max_index - 1; i++)
    {
        printf("%d ", line[i]);
    }
    for (int i = max_index + m; i >= max_index; i--)
    {
        printf("%d ", line[i]);
    }
    for (int i = max_index + 1 + m; i <= n; i++)
    {
        printf("%d ", line[i]);
    }

    return 0;
}

// to find the lenth of the decnt line,begin with line[now]
int After(int now, int line[], int n)
{
    int cnt = 0;
    if (line[now] > line[(now--) - 1] && now < n)
    {
        cnt++;
    }
    return cnt;
}

*/