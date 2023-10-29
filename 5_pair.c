// 23.10.27
// homework
// by HHC

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX 112 // must change to 1000012
#define my_min(a, b) (a > b ? b : a)

int legal(int t, int a[], int b[], int m);
int find(int num, int a[], int n);

int main()
{
    // input
    int n = 0, m = 0, t = 0, a[MAX] = {0}, b[MAX] = {0};
    scanf("%d%d%d", &n, &m, &t);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &b[i]);
    }

    // legal test
    if (!legal(t, a, b, m))
    {
        printf("-1");
        return 0;
    }

    // // creat the new a[]
    // for (int i = 0; i < n; i++)
    // {
    //     a[i] = t - a[i];
    //     if (a[i] < 0)
    //     {
    //         n = i;
    //         break;
    //     }
    // }

    // creat the new b[]
    int newb[MAX] = {0}, newm = 0;
    for (int j = 0; j < m; j++)
    {
        if (t - b[j] >= 0)
        {
            newb[newm++] = t - b[j]; // when leave: index 0~newm-1 is meaningful;total is newm
        }
    }

    int min = INT_MAX;
    for (int i = 0; i < newm; i++)
    {
        int num = newb[i];
        min = my_min(min, find(num, a, n));
    }

    printf("%d", min);

    return 0;
}

// useless code
//  int min = INT_MAX;
//  for (int i = n - 1; i >= 0; i--)
//  {
//      for (int j = 0; j < m; j++)
//      {
//          if (a[i] - b[j] >= 0)
//          {
//              min = my_min(min, a[i] - b[j]);
//          }
//      }
//  }

// // try
// int min = INT_MAX,
//     min_before = INT_MAX,
//     first = 1;
// for (int index = 0, left = 0, right = n - 1;
//      index < n && abs(left - right) <= 1; index = (right + left) / 2)
// {
//     for (int j = 0; j < m; j++)
//     {
//         if (t > a[index] + b[j])
//         {
//             min = my_min(min, t - a[index] - b[j]);
//         }
//     }
//     if (min == 0)
//     {
//         break;
//     }
//     else if (min == min_before)
//     {
//         right = index;
//     }
//     else if (min < min_before)
//     {
//         left = index;
//     }
//     if (first == 1)
//     {
//         min_before = min;
//         first = 0;
//         index = n / 2;
//     }
// }

//     printf("%d", min);

//     return 0;
// }

/****************************************
 * legal test:t>=a[+b[]
 *
 * TESTED
 */
int legal(int t, int a[], int b[], int m)
{
    int i = 0, dif = t - a[0], flag = 0;
    for (; i < m; i++)
    {
        if (dif >= b[i])
        {
            flag = 1;
            break;
        }
    }
    return flag;
}

/*****************************************
 * find  the most close stastic in a[](and num>a[])
 * return diffence= num - a[]  >= 0 (MIN)
 *
 *
 */
int find(int num, int a[], int n)
{
    int low = 0, high = n - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (num >= a[mid])
        {
            low = mid + 1;
        }
        else if (num < a[mid])
        {
            high = mid - 1;
        }
        // else//a[mid]==num
        // {
        //     return mid
        // }
    }

    int diffence = num - a[high];
    while (diffence < 0)
    {
        high--;
        diffence = num - a[high];
    }
    return diffence;
}