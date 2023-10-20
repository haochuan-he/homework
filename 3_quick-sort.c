/*version 2.0*/
// 23.10.17
// homework
// by HHC

#include <stdio.h>
#define MAX 1000 // 1000012 on OJ

int loop(int l, int r, int num[MAX], int pivot);

int main()
{
    int n = 0, k = 0, pivot = 0, num[MAX] = {0};
    scanf("%d%d", &n, &k);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &num[i]);
    }
    pivot = num[k - 1];

    int l = 0, r = n - 1;

    loop(l, r, num, pivot);

    int now = 0;
    for (; num[now] != pivot; now++)
        ;

    for (int i = 0; i < now; i++)
    {
        if (num[i] > pivot)
        {
            num[now] = num[i];
            num[i] = pivot;
            break;
        }
    }
    for (int j = n - 1; j > now; j--)
    {

        if (num[j] < pivot)
        {
            num[now] = num[j];
            num[j] = pivot;
            break;
        }
    }
    for (int i = 0; i < n; i++)
    {
        printf("%d ", num[i]);
    }

    return 0;
}

int loop(int l, int r, int num[MAX], int pivot)
{

    for (; l != r && num[l] < pivot; l++)
        ;
    for (; r != l && num[r] >= pivot; r--)
        ;
    if (r != l)
    {
        int tem = num[l];
        num[l] = num[r];
        num[r] = tem;
        return loop(l, r, num, pivot);
    }
    else
    {
        return 0;
    }
}

/*vwesion 1.0
include 'goto'
// 23.10.17
// homework
// by HHC

#include <stdio.h>
#define MAX 1000 // 1000012 on OJ

int main()
{
    int n = 0, k = 0, pivot = 0, num[MAX] = {0};
    scanf("%d%d", &n, &k);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &num[i]);
    }
    pivot = num[k - 1];

    int l = 0, r = n - 1;
here:
    for (; l != r && num[l] < pivot; l++)
        ;
    for (; r != l && num[r] >= pivot; r--)
        ;
    if (r != l)
    {
        int tem = num[l];
        num[l] = num[r];
        num[r] = tem;
        goto here;
    }

    int now = 0;
    for (; num[now] != pivot; now++)
        ;

    for (int i = 0; i < now; i++)
    {
        if (num[i] > pivot)
        {
            num[now] = num[i];
            num[i] = pivot;
            break;
        }
    }
    for (int j = n - 1; j > now; j--)
    {

        if (num[j] < pivot)
        {
            num[now] = num[j];
            num[j] = pivot;
            break;
        }
    }
    for (int i = 0; i < n; i++)
    {
        printf("%d ", num[i]);
    }

    return 0;
}
*/

/*
not conpletely follow the algorithm

// 23.10.16
// homework
// by HHC

#include <stdio.h>

#define MAX 1000 // 1000000 on OJ

int quence(int num[MAX], int pivot, int at, int l_at, int r_at);

int main()
{
    int n = 0, k = 0, pivot = 0;
    scanf("%d%d", &n, &k);
    int num[MAX] = {0};
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &num[i]);
    }
    pivot = num[k - 1];

    quence(num, pivot, k - 1, 0, n - 1);

    // output
    int i = 0;
    for (; num[i] != pivot; i++)
        ;
    for (int j = 0; j < i; j++)
    {
        if (num[j] > pivot)
        {
            int tem = num[j];
            num[j] = pivot;
            num[i] = tem;
        }
    }
    for (int j = n - 1; j > i; j--)
    {
        if (num[j] < pivot)
        {
            int tem = num[j];
            num[j] = pivot;
            num[i] = tem;
        }
    }

    for (int m = 0; m < n; m++)
    {
        if (m == 0)
        {
            printf("%d", num[m]);
        }
        else
            printf(" %d", num[m]);
    }
    return 0;
}

int quence(int num[MAX], int pivot, int at, int l_at, int r_at)
{

    int l = l_at, r = r_at;
    for (; l < (at) && num[l] < pivot; l++)
        ;
    for (; r > (at) && num[r] >= pivot; r--)
        ;
    int now = 0;
    for (; num[now] != pivot; now++)
        ;
    if (r != l)
    {
        int tem = num[l];
        num[l] = num[r];
        num[r] = tem;
        return quence(num, pivot, now, l, r);
    }
    else
    {
        return 0;
    }
}
*/