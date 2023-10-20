// 23.10.16
// homework
// by HHC

#include <stdio.h>
#include <string.h>
#define MAX 36

int main()
{
    int len = 0, N = 0;
    scanf("%d%d", &len, &N);
    getchar();

    char input[MAX];
    fgets(input, MAX, stdin);

    // transform the char to int
    int trans[MAX] = {0}; // begin form index 1; index 0 reserved for flag
    for (int i = 0; i < len; i++)
    {
        if ('0' <= input[i] && input[i] <= '9')
        {
            trans[i + 1] = input[i] - '0';
        }
        else if ('A' <= input[i] && input[i] <= 'Z')
        {
            trans[i + 1] = input[i] - 'A' + 10;
        }
    }

    // legal test

    for (int i = 1; i <= len; i++)
    {
        if (trans[i] > N - 1)
        {
            trans[0] = 1; // 1 for illgal ;0 for legal
        }
    }

    if (trans[0] == 0)
    {
        int zero_pass = 1, sum = 0;
        for (int i = 1; trans[i] == 0; i++, zero_pass++) // index(zero_pass)is the first meaningful number
            ;

        for (int i = zero_pass; i <= len; i++)
        {
            sum = sum * N + trans[i];
        }
        printf("%d", sum);
    }
    else
    {
        printf("Error");
    }

    return 0;
}
