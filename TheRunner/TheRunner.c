// 24.1.28
// for homework
// by HHC

#include <conio.h> // 必须
#include <stdio.h>
#include <windows.h> // 必须
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

HANDLE consoleHandle; // 操作控制台（也就是那个黑框框）需要的一个变量
int w, h;             // 高度，宽度，对应 y 和 x

void Mvaddch(int y, int x, char ch);
void MvaddchCol(int y, int x, char ch);
void Runway(int y, int x);
//
//
//
int main()
{
    // 初始化
    /******************************************************************************/

    // 显示界面初始化
    consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);  // 初始化这个操作器
    CONSOLE_SCREEN_BUFFER_INFO csbi;                  // 屏幕的信息
    GetConsoleScreenBufferInfo(consoleHandle, &csbi); // 获取屏幕信息
    w = csbi.dwSize.X;
    h = csbi.dwSize.Y; // 得到宽度高度
    // 游戏里面，如果一直有输入的光标，就有点不好看。我们可以让它不显示
    CONSOLE_CURSOR_INFO cci; // 光标信息
    cci.dwSize = 100;
    cci.bVisible = FALSE;                      // 不可见
    SetConsoleCursorInfo(consoleHandle, &cci); // 将光标特性应用到控制台
                                               // 到这里，闪烁的光标就消失了。

    // 游戏数据初始化
    int speed = 0, score = 0;

    srand(time(0)); // 以当前时间为随机数生成器的种子
    int random_variable = rand();
    // printf("Random value on [0,%d]: %d\n", RAND_MAX, random_variable);

    /********************************************************************************/

    // 循环控制
    /************************************************************************************/
    while (1)
    {
        Runway(h, w);

        while (kbhit() != 0)
        {                      // 如果它检测到有键盘敲击，返回非零。没有则返回 0
            char ch = getch(); // 有键盘敲击，我们获取是哪一个键

            Sleep(1000); // 程序暂停 1000 毫秒
        }
        Sleep(100 - speed);
    }
    // 游戏结束，我们要恢复光标显示
    cci.bVisible = TRUE;                       // 可见
    SetConsoleCursorInfo(consoleHandle, &cci); // 重新设置
}
//
//
//

/***************************************************************
 * void Mvaddch(int y, int x, char ch)
 *
 *在屏幕上 y, x 的位置打印一个 ch
 *类似地，你可以以这种方式定义一些在某个位置打印字符串的函数
 *
 **************************************************************/
void Mvaddch(int y, int x, char ch)
{
    COORD co = (COORD){.X = x, .Y = y};
    SetConsoleCursorPosition(consoleHandle, co); // 设置你的光标位置
    putchar(ch);                                 // 在这里打印一个字符
}

/*******************************************************************
 *void MvaddchCol(int y, int x, char ch)
 *
 *在x处打印布满屏幕的一列，均为ch
 *
 * 需要传入（屏幕高度，期望出现的x坐标，打印字符）
 *
 **********************************************************************/
void MvaddchCol(int y, int x, char ch)
{
    for (int col = 0; col < y; col++)
    {
        Mvaddch(col, x, ch);
    }
}

/**************************************************************************
 *void Runway(int y, int x)
 *
 *显示跑道界限和人物
 *
 *需要传入（屏幕高度，屏幕宽度）;详细参数可在函数内调整
 *
 * ************************************************************************/
void Runway(int y, int x)
{
    char CharOfRunway = '|'; // 显示跑道
    MvaddchCol(y, x / 3, CharOfRunway);
    MvaddchCol(y, 4 * x / 9, CharOfRunway);
    MvaddchCol(y, 5 * x / 9, CharOfRunway);
    MvaddchCol(y, 2 * x / 3, CharOfRunway);

    Mvaddch(3 * y / 4, x / 2, '*'); // 显示人物
}