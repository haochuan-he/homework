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
    // test_3();
    /*
    \033 || \e
    \033[31m：红色
    \033[32m：绿色
    \033[33m：黄色
    \033[34m：蓝色
    \033[35m：洋红色
    \033[36m：青色
    \033[37m：白色

    \033[3m：设置文字颜色
    \033[1m：设置文字粗体
    \033[0m：重置文字格式

    \033[3m斜体
    \033[4m下划线

    */
    printf("\e[31m");          // 设置文字颜色为红色
    printf("Hello, World!\n"); // 输出红色粗体文字

    printf("\e[1m");           // 设置文字粗体
    printf("Hello, World!\n"); // 输出红色粗体文字

    printf("\033[32m");
    printf("Hello, World!\n");

    printf("\033[33m");
    printf("Hello, World!\n");

    printf("\033[34m");
    printf("Hello, World!\n");

    printf("\033[35m");
    printf("Hello, World!\n");

    printf("\033[36m");
    printf("Hello, World!\n");

    printf("\033[37m");
    printf("Hello, World!\n");

    printf("\033[2m"); // 半透明?
    printf("Hello, World!\n");

    printf("\033[3m"); // 斜体（有点艺术感
    printf("Hello, World!\n");

    printf("\033[4m"); // 下划线
    printf("Hello, World!\n");
    Sleep(1000);
    printf("\033[2J"); // 可以清屏2J

    printf("\033[0m"); // 重置文字格式
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