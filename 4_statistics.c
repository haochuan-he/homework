// 23.10.21
// homework
// by HHC

#include <stdio.h>
#define MAX 1012
int main()
{
    int n = 0;
    scanf("%d", &n);
    getchar();

    // input the string
    int list[2 * 26][3] = {0}, ch;

    for (int i = 1; i < n + 1; i++)
    {
        ch = getchar();
        if ('a' <= ch && ch <= 'z')
        {
            list[ch - 'a'][1]++;
        }
        else
        {
            list[26 + ch - 'A'][1]++;
        }
    }

    int max = 0;
    for (int i = 0; i < 52; i++)
    {
        if (max < list[i][1])
        {
            max = list[i][1];
        }
        // if (list[i][1] == 0)
        // {
        //     list[i][0] = -1; // flag of skip
        // }
        // if (list[i][1] != 0 && list[i + 26][1] != 0)
        // {
        //     list[i][0] = 1;
        //     list[i + 26][0] = 1;
        // }
    }

    // to culculate the real output position into list[][2];
    int cnt = 0; // include space

    // for the lowwer
    for (int i = 0; i < 26; i++)
    {
        if (list[i][1] != 0)
        {
            cnt++;
            list[i][2] = cnt++; // space || for match upper
            // check the corresponding upper
            if (list[i + 26][1] != 0)
            {
                list[i + 26][2] = cnt++; // space
            }
        }
        else if (list[i + 26][1] != 0)
        {
            {
                cnt++;
                list[i + 26][2] = cnt++; // space
            }
        }
    }
    // // for the rest upper
    // for (int i = 26; i < 52; i++)
    // {
    //     if (list[i][1] != 0 && list[i][2] == 0)
    //     {
    //         cnt++;
    //         list[i][2] = cnt++; // space
    //     }
    // }

    int final[MAX][2], space;
    for (int i = 1; i < cnt + 1; i++)
    {
        final[i][0] = 0;
        final[i][1] = 0;
    }
    for (int i = 1; i < 1 + cnt;)
    {
        space = 1;
        for (int j = 0; j < 52; j++)
        {
            if (list[j][2] == i) // find the letter in quence to print
            {
                final[i][0] = j; // j is the rank in list,which can be transform to letter
                final[i][1] = list[j][1];
                i++;
                space = 0;
                break;
            }
        }
        if (space == 1)
        {
            final[i][1] = -1;
            i++;
        }
    }

    // print"="
    for (int row = max; row > 0; row--)
    {
        for (int col = 1; col < 1 + cnt; col++)
        {
            if (final[col][1] >= row)
            {
                printf("=");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
    // print'-'
    for (int i = 1; i < cnt; i++)
    {
        printf("-");
    }
    printf("\n");

    // print letter
    for (int i = 1; i < 1 + cnt; i++)
    {
        if (final[i][1] == -1)
        {
            printf(" ");
        }
        else if (final[i][0] < 26)
        {
            printf("%c", final[i][0] + 'a');
        }
        else
        {
            printf("%c", final[i][0] - 26 + 'A');
        }
    }

    return 0;
}