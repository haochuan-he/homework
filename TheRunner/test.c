#include <conio.h> // 必须
#include <stdio.h>
#include <windows.h> // 必须
#include <stdlib.h>
#include <time.h>

int main()
{
    while (1)
    {
        char ch, add;
        ch = add = '\0';
        while (kbhit() != 0)
        {                 // 如果它检测到有键盘敲击，返回非零。没有则返回 0
            ch = getch(); // 有键盘敲击，我们获取是哪一个键
        }
        Sleep(100);
        while (kbhit() != 0)
        {
            fflush(stdin);
            // 如果它检测到有键盘敲击，返回非零。没有则返回 0
            add = getch(); // 有键盘敲击，我们获取是哪一个键
        }

        printf("ch=%c add=%c\n", ch, add);
        Sleep(1000);
    }
}