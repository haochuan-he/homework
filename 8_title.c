// 23.11.265
// for homework
// by HHC

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 5012

int main()
{
    char *str = malloc(MAX * sizeof(*str));
    char ch;
    int flag = 1;
    for (; (ch = getchar()) != '!';)
    {
        ch = tolower(ch);
        if (flag == 1)
        {
            ch = toupper(ch);
            flag = 0;
        }
        if (ch == ' ')
        {
            flag = 1;
        }
        putchar(ch);
    }
    free(str);
    return 0;
}

// int main()
// {
//     char *str = malloc(MAX * sizeof(*str));

//     while (1)
//     {
//         for (int i = 0; i < MAX; i++)
//         {
//             *str = '0';
//         }
//         scanf("%s", str);
//         if (*str == EOF)
//         {
//             break;
//         }
//         *str = toupper(*str);
//         int len = strlen(str);
//         for (int i = 1; i < len; i++)
//         {
//             *(str + i) = tolower(*(str + i));
//         }
//         printf("%s ", str);
//     }
//     free(str);

//     return 0;
// }