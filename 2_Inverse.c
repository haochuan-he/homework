// 23.10.8 20点15分
// homework
// by HHC

#include <stdio.h>

#define MAXSIZE 10000012

int main()
{
    int input[MAXSIZE] = {0};
    int n = 0, k = 0;
    char ch;
    scanf("%d", &n);
    getchar(); // may error

    for (int i = 0; i < n; i++)
    {
        ch = getchar();
        input[i] = ch;
    }

    scanf("%d", &k);

    for (int i = k - 1; i >= 0; i--)
    {
        printf("%c", input[i]);
    }
    for (int i = n - 1; i >= k; i--)
    {
        printf("%c", input[i]);
    }

    return 0;
}