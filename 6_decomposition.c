// 23.11.13
// for homework
// by HHC

#include <stdio.h>
#define MAX 42

int ans[MAX];

int findDecomposition(int n, int min, int nFound);

int main()
{
    int n = 0;
    scanf("%d", &n);

    findDecomposition(n, 1, 0);

    return 0;
}

int findDecomposition(int n, int min, int nFound)
{
    if (n == 0)
    {
        for (int i = 0; ans[i] != 0 && i < nFound; i++)
        {
            printf("%d ", ans[i]);
        }
        printf("\n");
        return 1;
    }
    else if (n < min)
    {
        return 0;
    }

    for (int i = min; i <= n; i++)
    {
        ans[nFound] = i;
        findDecomposition(n - i, i, nFound + 1);
    }
    return 0;
}
