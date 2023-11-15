// 23.11.12
// for homework
// by HHC

#include <stdio.h>

int f[100012] = {0};
int Find(int boss);
int main()
{
    int n = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &f[i]);
    }

    for (int i = 1; i <= n; i++)
    {
        f[i] = Find(i);
    }

    for (int i = 1; i <= n; i++)
    {
        printf("%d ", f[i]);
    }
    return 0;
}

int Find(int boss)
{
    if (f[boss] == boss)
    {
        return boss;
    }
    else
    {
        return Find(f[boss]);
    }
}