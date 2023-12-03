// 23.12.2
// for homework
// by HHC

#include <stdio.h>
#include <string.h>

#define MAX1 1012
#define MAX2 2012

int function(int d1, int d2, int size, char s1[], char s2[]);

int main()
{
    int t = 0;
    scanf("%d", &t);

    while (t--)
    {
        // input
        getchar();
        char s1[MAX1], s2[MAX1]; // s3[MAX2];
        memset(s1, '\0', MAX1);
        memset(s2, '\0', MAX1);
        // memset(s3, '\0', MAX2);
        int d1 = 0, d2 = 0, size = 0;
        int len1 = 0, len2 = 0;

        char ch;
        while ((ch = getchar()) != ';')
        {
            s1[len1++] = ch;
        }
        while ((ch = getchar()) != ';')
        {
            s2[len2++] = ch;
        }
        scanf("%d;%d;%d", &d1, &d2, &size);

        function(d1, d2, size, s1, s2);

        // for test
        // printf("\n--%d,%d,%d,(%d,%d)%s,%s--\n", d1, d2, size, len1, len2, s1, s2);
    }

    return 0;
}

int function(int d1, int d2, int size, char s1[], char s2[])
{
    char s3[MAX2];
    memset(s3, '\0', MAX2);
    int len1 = strlen(s1), len2 = strlen(s2);
    int flag = 1;
    for (char *p1 = s1, *p2 = s2, *p3 = s3; *p1 != '\0' || *p2 != '\0';)
    {
        if (*p1 == '\0')
        {
            while ((*p3++ = *p2++) != '\0')
                ;
            *(s3 + size - 1) = '\0';
            // printf("out1");
            break;
        }
        else if (*p2 == '\0')
        {
            while ((*p3++ = *p1++) != '\0')
                ;
            *(s3 + size - 1) = '\0';
            // printf("out2");
            break;
        }
        else if ((p3 - s3) >= size)
        {
            *(s3 + size - 1) = '\0';
            // printf("out3");
            break;
        }
        else if (flag == 1)
        {
            flag = 2;
            for (int i = 0; i < d1 && *p1 != '\0'; i++)
            {
                *p3++ = *p1++;
                // printf("test1=%s\n", s3);
            }
        }
        else if (flag == 2)
        {
            flag = 1;
            for (int i = 0; i < d2 && *p2 != '\0'; i++)
            {
                *p3++ = *p2++;
                // printf("test2=%s\n", s3);
            }
        }
        else
        {
            printf("wrong!!!");
            return 1;
        }
    }
    // printf("ok");
    printf("%s\n", s3);
    return 0;
}