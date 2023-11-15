// 23.11.12
// for homework
// by HHC

// 可把所有数据排序，序数保存，区间即为某个序数的前两个的下标
#include <stdio.h>
int bucket[12][3]; // 100012
int Max(int l, int r);
int main()
{ // input
    int n = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &bucket[i][0]);
    }

    Max(1, n);

    // output
    for (int i = 1; i <= n; i++)
    {
        printf("%d %d\n", bucket[i][1], bucket[i][2]);
    }

    return 0;
}

int Max(int l, int r)
{
    // find the base task
    if (l > r)
    {
        return 0;
    }
    else if (l == r)
    {
        bucket[l][1] = l;
        bucket[l][2] = l;
    }

    // function
    int max = l;
    for (int i = l; i <= r; i++)
    {
        if (bucket[i][1] == 0 && bucket[i][0] > bucket[max][0])
        {
            max = i;
        }
    }
    bucket[max][1] = l;
    bucket[max][2] = r;

    // find the smaller task
    return Max(l, max - 1) + Max(max + 1, r);
}

// #include <stdio.h>
// int bucket[12][3]; // 100012
// int Max(int left, int right, int now);
// int main()
// { // input
//     int n = 0;
//     scanf("%d", &n);
//     for (int i = 1; i <= n; i++)
//     {
//         scanf("%d", &bucket[i][0]);
//     }

//     // find the first step
//     Max(1, n, 0);

//     // output
//     for (int i = 1; i <= n; i++)
//     {
//         printf("%d %d\n", bucket[i][1], bucket[i][1]);
//     }

//     return 0;
// }

// int Max(int left, int right, int now)
// {
//     int flag = 1;
//     // the smallest task
//     if (left >= right)
//     { // do no thing
//         return 0;
//     }
//     else if (left == 1)
//     {
//         flag = 0;
//     }

//     // find the max
//     int max = left, max_2 = left, max_3 = right;
//     {
//         for (int i = left; i <= right; i++)
//         {
//             if (bucket[i][1] == 0 && bucket[i][0] > bucket[max][0])
//             {
//                 max_3 = max_2;
//                 max_2 = max;
//                 max = i;
//             }
//         }
//     }
//     now = max;
//     if (max_2 > max_3)
//     {
//         bucket[max][1] = (max_3 - 1) * flag + 1;
//         bucket[max][2] = max_2;
//     }
//     else
//     {
//         bucket[max][2] = max_3;
//         bucket[max][1] = (max_2 - 1) * flag + 1;
//     }

//     // find the smaller task
//     return Max(left, now - 1, now) +
//            Max(now + 1, right, now);
// }