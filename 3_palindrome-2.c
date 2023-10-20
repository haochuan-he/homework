// 23.10.16
// homework
// by HHC

#include <stdio.h>
#define MAXSIZE 1000 // must change on OJ

int main()
{
    int len = 0;
    scanf("%d", &len);

    getchar();

    char input[MAXSIZE] = {'0'};

    for (int i = 0; i < len; i++)
    {
        input[i] = getchar();
    }

    for (int i = 0; i < len; i++)
    {
        if (input[i] == '?')
        {
            input[i] = input[len - i - 1];
        }
    }

    // for (int i = 0; i < len; i++)
    // {

    //     printf("%c", input[i]);
    // }

    // fill the "?"
    int fill = 1;
    int goodfill[100];
    for (int i = 0; i < 100; i++)
    {
        // if (i % 10 == i / 10)
        // {
        //     goodfill[i] = -1; // flag
        // }
        // else
        // {
        //     goodfill[i] = i;
        // }
        goodfill[i] = i;
    }

    int library[MAXSIZE][2];
    for (int i = 0; i < MAXSIZE; i++)
    {
        library[i][0] = 0;
        library[i][1] = 0;
    }
    for (int i = 0, good = 0; i < (len / 2); i++)
    {
        if (input[i] == '?')
        {
            for (; goodfill[good] == -1; good++)
            {
                ;
            }
            library[i][0] = goodfill[good] / 10; // min half
            library[i][1] = goodfill[good] % 10;
            library[len - i - 1][0] = goodfill[good] % 10; // max half
            library[len - i - 1][1] = goodfill[good] / 10;
            goodfill[good] = -1;
            // goodfill[i % 10 * 10 + i / 10] = -1;
        }
    }

    // output
    for (int i = 0; i < len; i++)
    {
        if (input[i] != '?')
        {
            printf("%c", input[i]);
        }
        else
        {
            printf("%d%d", library[i][0], library[i][1]);
        }
    }

    return 0;
}