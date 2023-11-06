// 11.5
// for correct
// by HHC

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 12 // 100012

int main()
{
    int len = 0;
    char str[MAX];
    memset(str, '\0', MAX);

    scanf("%d", &len);
    scanf("%s", str);
    for (int i = 0; i < len; i++)
    {
        if ('a' <= str[len - i - 1] && str[len - 1 - i] <= 'z')
        {
            str[len - 1 - i] = toupper(str[len - 1 - i]);
        }
        else if ('A' <= str[len - i - 1] && str[len - 1 - i] <= 'Z')
        {

            str[len - 1 - i] = tolower(str[len - 1 - i]);
        }

        printf("%c", str[len - i - 1]);
    }
    // printf("%s", str);

    return 0;
}