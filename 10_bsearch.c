// 23.12.15
// for homework
// by HHC

#include <stdio.h>
#include <stdlib.h>

#define MAX 100 // 1000012

int cmp(const void *a, const void *b);

int main()
{
    int n = 0, q = 0, num[MAX] = {0};
    scanf("%d%d", &n, &q);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &num[i]);
    }
    for (int i = 0; i < q; i++)
    {
        int goal = 0, *ptr;
        scanf("%d", &goal);
        ptr = bsearch(&goal, num, n, sizeof num[0], cmp);
        if (ptr == NULL)
        {
            printf("-1\n");
        }
        else
        {
            printf("%d\n", ptr - num);
        }
    }

    return 0;
}

int cmp(const void *a, const void *b)
{
    const int *left = a;
    const int *right = b;
    return (*left > *right) - (*left < *right);
}