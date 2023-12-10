#include <stdio.h>
#include <ctype.h>

int main()
{
    char ch = getchar();
    ch = toupper(ch);
    putchar(ch);

    while ((ch = getchar()) != EOF)
    {
        if ('A' <= ch && ch <= 'Z')
        {
            putchar(' ');
            ch = tolower(ch);
            putchar(ch);
        }
        else
        {
            putchar(ch);
        }
    }
    return 0;
}