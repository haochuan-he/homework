// 23.12.2
// for homework
// by HHC

#include <stdio.h>
#include <string.h>
#define MAX 1036

int LegalCheck(char all[][MAX], int cnt, int legal[]);

int main()
{
    int legal[300] = {0};
    // 0 for illegal;1 for legal;
    //>1 for legal and need parse;

    char ch = '0';
    int index = 0;
    while ((ch = getchar()) != '\n')
    {
        if (ch == ':')
        {
            legal[index]++;
        }
        else
        {

            legal[ch] = 1;
            index = ch;
        }
    }

    char all[MAX][MAX];
    memset(all, '\0', MAX * MAX);
    int cnt = 0;
    while (scanf("%s", all[cnt++]) != EOF)
        ;
    cnt--;

    // check
    if (LegalCheck(all, cnt, legal))
    {
        return 0;
    }

    // output
    printf("%s\n", all[0]);
    for (int row = 1; row < cnt; row++)
    {
        if (all[row][0] == '-' && legal[all[row][1]] > 1)
        {
            printf("%c=%s\n", all[row][1], all[row + 1]);
            row++;
        }
        else if (all[row][0] == '-' && legal[all[row][1]] == 1)
        {
            printf("%c\n", all[row][1]);
        }
    }

    return 0;
}

int LegalCheck(char all[][MAX], int cnt, int legal[])
{
    for (int row = 1; row < cnt; row++)
    {
        if (all[row][0] == '-' && legal[all[row][1]] == 0)
        {
            printf("%s: invalid option -- '%c'", all[0], all[row][1]);
            return 1;
        }
        else if (all[row][0] == '-' && legal[all[row][1]] > 1) // may wrong
        {
            if (all[++row][0] == '\0')
            {
                printf("%s: option requires an argument -- '%c'", all[0], all[row - 1][1]);
                return 1;
            }
            row++;
        }
    }
    return 0;
}