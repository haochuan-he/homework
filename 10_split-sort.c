
// 23.12.15
// for homework
// by HHC

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100 // 1000000
#define max 112
int my_strcmp(const void *a, const void *b);
int main()
{
    char all[MAX], goal[MAX], part[MAX][max], *str = NULL; //*part[]
    memset(all, '\0', MAX);
    memset(part, '\0', max * MAX);
    memset(goal, '\0', MAX);
    scanf("%s", all);
    scanf("%s", goal);
    int cnt = 0;
    for (str = strtok(all, goal); str != NULL; str = strtok(NULL, goal))
    {
        strcpy(part[cnt++], str);
    }
    qsort(part, cnt, sizeof part[0], my_strcmp);
    // qsort(part, cnt, sizeof part[0], my_strcmp);
    for (int i = 0; i < cnt; i++)
    {
        printf("%s\n", part[i]);
    }
    return 0;
}

int my_strcmp(const void *a, const void *b)
{
    const char *left = a;
    const char *right = b;
    return strcmp(left, right);
}
int my_strcmp1(const void *a, const void *b)
{
    const char *const *left = a;
    const char *const *right = b;
    return strcmp(*left, *right);
}

// // 23.12.15
// // for homework
// // by HHC

// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
// #define MAX 100 // 1000000
// #define max 112

// int my_strcmp(const void *a, const void *b);

// int main()
// {
//     char all[MAX], goal = '0', small[MAX][max];
//     memset(all, '\0', MAX);
//     memset(small, '\0', max * MAX);
//     scanf("%s", all);
//     getchar();
//     goal = getchar();
//     all[strlen(all)] = goal;

//     char *tem = strtok(all, &goal);
//     if (tem == NULL)
//     {
//         printf("--wrong--goal=%c--\n", goal);
//         return 0;
//     }
//     // strcpy(small[0], tem);
//     // small[0] = *tem;
//     int cnt = 1;
//     for (int i = 1;; cnt++, i++)
//     {
//         if ((*tem = strtok(NULL, &goal) == NULL))
//         {
//             break;
//         }
//         else
//         {
//             strcpy(small[i], tem);
//         }
//     }
//     // qsort(small, cnt, sizeof small[0][0], strcmp);
//     qsort(small, cnt, sizeof small[0][0], my_strcmp);

//     for (int i = 0; i < cnt; i++)
//     {
//         printf("%s\n", small[i]);
//     }

//     return 0;
// }

// int my_strcmp(const void *a, const void *b)
// {
//     const char *left = a;
//     const char *right = b;
//     return strcmp(left, right);
// }