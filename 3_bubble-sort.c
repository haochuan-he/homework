// 23.10.15 19:10
// homework
// by HHC

#include <stdio.h>
#define MAXSIZE 50012
#define MAX 100012

int main()
{
    int t = 0;
    scanf("%d", &t);
    int ans[MAX] = {0};
    for (int u = 0; u < t; u++)
    {
        int total = 0;
        int num[MAXSIZE];
        scanf("%d", &total);
        getchar();
        for (int i = 0; i < total; i++)
        {
            scanf("%d", &num[i]);
        }

        for (int i = 0; i < total; i++)
        {
            if (num[i] > num[total - 1])
            {
                ans[u] = 1;
                break;
            }
        }

        if (ans[u] == 1)
        {
            printf("No\n");
        }
        else
        {
            printf("Yes\n");
        }
        // // origial code
        // for (int i = 0; i < total; i++)
        // {
        //     for (int j = 0; j < total - i - 2; j++)
        //     { // not j < n - i - 1
        //         if (a[j] > a[j + 1])
        //         {
        //             int tmp = a[j];
        //             a[j] = a[j + 1];
        //             a[j + 1] = tmp;
        //         }
        //     }
        // }

        // // test output
        // for (int i = 0; i < total; i++)
        // {
        //     printf("%d ", a[i]);
        // }
        //
        // the conclusion: last num must be max
    }

    return 0;
}