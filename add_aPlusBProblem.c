// 23.12.10
// for additional problem
// by HHC
#define Max(a, b) (a > b ? a : b)
#include <string.h>
#include <stdio.h>

#define MAX 10120

int Sum(char *p1, char *p2, int *p3, int cnt);
int main()
{
    char a[MAX], b[MAX];
    int sum[MAX];
    memset(a, '\0', MAX);
    memset(b, '\0', MAX);
    memset(sum, -1, MAX);

    while (scanf("%s%s", a + 1, b + 1) != EOF)
    {
        // printf("%s==%s\n", a + 1, b + 1);
        int len1 = strlen(a + 1), len2 = strlen(b + 1);
        // printf("len1=%d,len2=%d\n", len1, len2);
        int *p3 = sum + Max(len1, len2);
        int cnt = len1 + len2 - Max(len1, len2);
        // printf()

        if (len1 >= len2)
        {
            char *p1 = a + len1, *p2 = b + len2;
            // printf("1: *p1=%c,*p2=%c\n", *p1, *p2);
            Sum(p1, p2, p3, cnt);
        }
        else
        {
            char *p2 = a + len1, *p1 = b + len2;
            // printf("2: *p1=%c,*p2=%c\n", *p1, *p2);

            Sum(p1, p2, p3, cnt);
        }
        // int cnt = len1 + len2 - Max(len1, len2);
        // while (cnt--)
        // {
        //     *p3-- = atoi(*p1--) + atoi(*p2--);
        //     if (*(p3 + 1) >= 10)
        //     {
        //         *(p3 + 1) /= 10;
        //         (*p3)++;
        //     }
        // }
        for (int i = 0;; i++)
        {
            if (i != 0 && sum[i] == -1)
            {
                break;
            }
            if (sum[i] != -1)
            {
                printf("%d", sum[i]);
            }
        }
        printf("\n");
        memset(a, '\0', MAX);
        memset(b, '\0', MAX);
        memset(sum, -1, MAX);
    }

    return 0;
}

int Sum(char *p1, char *p2, int *p3, int cnt)
{
    int carry = 0;
    while (cnt--)
    {
        *p3-- = *p2-- - '0' + *p1-- - '0' + carry;
        carry = 0;
        if (*(p3 + 1) >= 10)
        {
            *(p3 + 1) %= 10;
            carry = 1;
        }
        // printf("--now*p3=%d--\n", *(p3 + 1));
    }
    while (*p1 != '\0')
    {
        *p3-- = *p1-- - '0' + carry;
        carry = 0;
        if (*(p3 + 1) >= 10)
        {
            *(p3 + 1) %= 10;
            carry = 1;
        }
        // printf("--next*p3=%d--\n", *(p3 + 1));
    }
    if (carry != 0)
    {
        *p3 = carry;
    }

    return 0;
}

// // 23.10.25
// // for additional problem
// // by HHC

// #include <stdio.h>
// #define MAX 1012
// #define my_max(a, b) (a > b ? a : b)

// int run_one_time(int loop);

// int main()
// {
//     int loop = 1;
//     run_one_time(loop);
//     return 0;
// }

// int run_one_time(int loop)
// {
//     loop--;
//     // input
//     int a[MAX] = {0}, i = 1, b[MAX] = {0}, j = 1, sum[MAX] = {0};
//     for (char ch; (ch = getchar()) != ' '; i++)
//     {
//         a[i] = ch - '0';
//     }
//     for (char ch; (ch = getchar()) != EOF; j++)
//     {
//         if (ch == '\n')
//         {
//             loop++;
//             break;
//         }
//         b[j] = ch - '0';
//     }

//     // calculate
//     int max = my_max(i, j);
//     int l = my_max(i, j);
//     for (; l > 0; l--) // ()WRONG when the a,b digit not equal
//     {
//         if (i > j)
//         {
//             if (j > 0)
//             {
//                 sum[l] = a[i] + b[j];
//                 i--;
//                 j--;
//             }
//             else
//             {
//                 sum[l] = a[i];
//                 i--;
//             }
//         }
//         else if (j > i)
//         {
//             if (i > 0)
//             {
//                 sum[l] = a[i] + b[j];
//                 i--;
//                 j--;
//             }
//             else
//             {
//                 sum[l] = b[j];
//                 j--;
//             }
//         }
//         else
//         {
//             sum[l] = a[l] + b[l];
//         }
//     }
//     for (l = max; l >= 0; l--)
//     {
//         if (sum[l] >= 10)
//         {
//             sum[l] = sum[l] % 10;
//             if (l > 0)
//             {
//                 sum[l - 1]++;
//             }
//         }
//     }

//     for (int t = (1 - (sum[0] != 0)); t < max; t++) // to judge the possible carry
//     {
//         printf("%d", sum[t]);
//     }
//     printf("\n");
//     if (loop > 0)
//     {
//         return run_one_time(loop);
//     }
//     return 0;
// }
// /*
// // 23.10.25
// // for additional problem
// // by HHC
// #include <stdio.h>
// #define MAX 1012
// #define min(a, b) (a > b ? b : a)

// int main()
// { // test
//   // for (int a = 0, b = 0; scanf("%d%d", &a, &b) != EOF;)
//   // {
//   //     printf("%d\n", a + b);
//   // }
//     int loop = 1;
// notend:
//     loop--;
//     // input
//     int a[MAX + 1] = {0}, i = MAX - 1, b[MAX + 1] = {0}, j = MAX - 1, sum[MAX + 1] = {0};

//     for (char ch; (ch = getchar()) != ' '; i--)
//     {
//         a[i] = ch - '0';
//     }
//     for (char ch; (ch = getchar()) != EOF; j--)
//     {
//         if (ch == '\n')
//         {
//             loop++;
//             break;
//         }
//         b[j] = ch - '0';
//     }

//     // calculate
//     int l = min(i, j);
//     for (; l <= MAX; l++)
//     {
//         sum[l] += a[l] + b[l];
//         if (sum[l] >= 10)
//         {
//             sum[l] /= 10;
//             sum[l + 1] = sum[l] % 10;
//         }
//     }

//     for (int t = (MAX - 1) + (sum[t] != 0); t >= min(i, j); t--) // judge if exsist the highest digit carry
//     {
//         printf("%d", sum[t]);
//     }
//     printf("\n");

//     if (loop > 0)
//     {
//         goto notend;
//     }

//     return 0;
// }*/
