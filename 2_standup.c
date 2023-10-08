// 23.10.8 20点29分
// homework
//  by HHC

#include <stdio.h>
#define MAXSIZE 100012

int main()
{
    int amount_s[MAXSIZE] = {0}, n = 0, sum = 0, diffence_max = 0;
    scanf("%d", &n);
    for (int i = 0; i <= n; i++)
    {
        scanf("%d", &amount_s[i]);
        sum += amount_s[i];

        if (amount_s[i] != 0)
        {
            if ((i - sum + amount_s[i]) > diffence_max)
            {
                diffence_max = i - sum + amount_s[i];
            }
        }
    }
    printf("%d", diffence_max);

    return 0;
}