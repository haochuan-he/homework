// 23.11.26
// for homework
// by HHC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100012 // 100012

int main()
{
    // char *s = malloc(MAX * sizeof(*s)), *t = malloc(MAX * sizeof(*t));
    char *s = NULL, *t = NULL;
    if ((s = malloc(MAX * sizeof(*s))) == NULL)
    {
        printf("*s allocation failed\n");
        return 0;
    }
    if ((t = malloc(MAX * sizeof(*t))) == NULL)
    {
        printf("*t allocation failed\n");
        return 0;
    }
    scanf("%s%s", s, t);
    int len1 = strlen(s), len2 = strlen(t), flag = 0;
    for (int i = 0; i < len1; i++)
    {
        if (*(s + i) == *(t + flag))
        {
            flag++;
        }
        else
        {
            if (*(s + i) == *t)
            {
                flag == 1;
            }
            else
            {
                flag = 0;
            }
        }
        if (flag == len2)
        {
            printf("%d ", i - len2 + 1);
            i = i - len2 + 1;
            flag = 0;
        }
    }
    free(s);
    free(t);
    return 0;
}

// int main()
// {
//     char *s = NULL, *t = NULL;
//     s = malloc(MAX * sizeof(*s));
//     t = malloc(MAX * sizeof(*t));

//     if (s == NULL || t == NULL)
//     {
//         return 0;
//     }

//     char ch = '0';
//     int i = 0, j = 0;
//     for (; (ch = getchar()) != '\n'; i++)
//     {
//         *(s + i) = ch;
//     }

//     for (; (ch = getchar()) != '\n' && ch != EOF; j++)
//     {
//         *(t + j) = ch;
//     }
//     int len_all = i, len_aim = j, mem = -1;
//     i = 0, j = 0;
//     for (int k = 0; k <= len_all; k++)
//     {
//         if (*(s + k) == *(t + i))
//         {
//             // printf("there1");
//             i++;
//             if (mem == -1)
//             {
//                 mem = k;
//             }
//             if (i == len_aim)
//             {
//                 printf("%d ", mem);
//                 k = mem++;
//                 i = 0;
//                 if (*(s + k) == *t)
//                 {
//                     i = 1;
//                 }
//             }
//         }
//         else
//         // printf("there2");
//         {
//             if (*(s + k) == *t)
//             {
//                 mem = k;
//                 i = 1;
//             }
//             else
//             {
//                 mem = -1;
//                 i = 0;
//             }
//         }
//     }

//     free(s);
//     free(t);

//     return 0;
// }