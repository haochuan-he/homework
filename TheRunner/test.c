#include <conio.h> // 必须
#include <stdio.h>
#include <windows.h> // 必须
#include <stdlib.h>
#include <time.h>

void test_1(); // awful
void test_2(); // may be a viable version
void test_3(); // a excellent version for input, but may not for a game

int main()
{
    // test_1();
    // test_2();
    test_3();
}

void test_3()
{

    while (1)
    {
        char ch, add;
        ch = add = '\0';

        while (kbhit() != 0)
        {
            add = ch;
            ch = getch();
            Sleep(150);
        }

        printf("ch=%c add=%c\n", ch, add);
        Sleep(150);
        // Sleep(1000);
    }
}

void test_2()
{
    while (1)
    {
        char ch, add;
        ch = add = '\0';

        if (kbhit() != 0)
        {                 // 如果它检测到有键盘敲击，返回非零。没有则返回 0
            ch = getch(); // 有键盘敲击，我们获取是哪一个键
        }

        if (kbhit() != 0)
        {

            // 如果它检测到有键盘敲击，返回非零。没有则返回 0
            add = getch(); // 有键盘敲击，我们获取是哪一个键
        }

        printf("ch=%c add=%c\n", ch, add);
        // Sleep(150);
        Sleep(1000);
    }
}

void test_1()
{
    while (1)
    {
        char ch, add;
        ch = add = '\0';
        Sleep(150);

        while (kbhit() != 0)
        {                 // 如果它检测到有键盘敲击，返回非零。没有则返回 0
            ch = getch(); // 有键盘敲击，我们获取是哪一个键
        }
        Sleep(150);
        while (kbhit() != 0)
        {
            fflush(stdin);
            // 如果它检测到有键盘敲击，返回非零。没有则返回 0
            add = getch(); // 有键盘敲击，我们获取是哪一个键
        }

        printf("ch=%c add=%c\n", ch, add);
    }
}