// 23.12.2
// for homework
// by HHC

#include <stdio.h>
#include <string.h>
#define MAX 1012

void Mystrcat(char s1[], char s2[]);

int main()
{
    char s1[MAX], s2[MAX];
    int t = 0;
    scanf("%d", &t);
    // loop for t times
    while (t--)
    {
        // memset(s1, '0', MAX);
        // memset(s2, '0', MAX);
        scanf("%s%s", s1, s2);
        Mystrcat(s1, s2);
    }
    return 0;
}

void Mystrcat(char s1[], char s2[])
{
    int len1 = strlen(s1), len2 = strlen(s2);
    int cnt = 0;
    char *ptr1 = s1, *ptr2 = s2, ans[2 * MAX];
    for (int i = 0, j = 0; (*(ptr1 + i) != '\0') && j < len2;)
    {
        if (*(ptr1 + i) == *(ptr2 + j))
        {
            if (*(ptr1 + i + 1) == '\0')
            {
                cnt = j + 1;
                break;
            }
            i++;
            j++;
        }
        else
        {
            ptr1 = ptr1 + 1; // maybe i
            j = 0;
            i = 0;
        }
    }
    for (int i = 0; i < len1; i++)
    {
        ans[i] = s1[i];
    }

    for (int j = cnt; j <= len2; j++) //<=,include\0
    {
        ans[len1++] = s2[j];
    }
    printf("%s\n", ans);
    return;
}