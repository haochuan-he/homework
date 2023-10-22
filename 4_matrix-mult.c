// 23.10.21
// homework
// by HHC

#include <stdio.h>
#define MAX 112

int main()
{
    int m, n, p;
    scanf("%d%d%d", &m, &n, &p);
    int A[MAX][MAX] = {0}, B[MAX][MAX] = {0}, out[MAX][MAX] = {0};

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &A[i][j]);
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < p; j++)
        {
            scanf("%d", &B[i][j]);
        }
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < p; j++)
        {
            int sum = 0;
            for (int l = 0; l < n; l++)
            {
                sum += A[i][l] * B[l][j];
            }
            out[i][j] = sum;
        }
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < p; j++)
        {
            printf("%d ", out[i][j]);
        }
        printf("\n");
    }

    return 0;
}