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

typedef struct Obstacle // 障碍物，数组中1，2，3分别表示左中右道中障碍物y坐标;一列中可以多个
{
    int Down[5][3];

} Obstacle;

void Mvaddch(int y, int x, char ch);
void MvaddchCol(int y, int x, char ch);
void MvaddchRow(int y, int x, char ch[]);
void MvaddchMiddle(int y, int x, int runway, char ch);
void Display(int y, int x, int man, int score, int speed, Obstacle obstacle);
void InitObstacle(Obstacle *obstacle);
void GenerateObstacle(Obstacle *obstacle, int random);
void MoveObstacle(Obstacle *obstacle, int y);

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
    int speed = 0, score = 0, man = 2;
    Obstacle obstacle;
    InitObstacle(&obstacle);

    srand(time(0)); // 以当前时间为随机数生成器的种子
    // printf("Random value on [0,%d]: %d\n", RAND_MAX, random_variable);

    /********************************************************************************/

    // 循环控制
    /************************************************************************************/
    while (1)
    {
        int random_variable = rand();
        GenerateObstacle(&obstacle, random_variable);
        Display(h, w, man, score, speed, obstacle);
        MoveObstacle(&obstacle, h);

        while (kbhit() != 0)
        {                      // 如果它检测到有键盘敲击，返回非零。没有则返回 0
            char ch = getch(); // 有键盘敲击，我们获取是哪一个键
            // Sleep(1000);       // 程序暂停 1000 毫秒
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

/*******************************************************************
 *void MvaddchRow(int y, int x, char ch[])
 *
 *从 x,y处开始打印字符串ch[]
 *
 * 需要传入（期望出现的y坐标，期望出现的x坐标，打印字符串）
 *
 **********************************************************************/
void MvaddchRow(int y, int x, char ch[])
{
    COORD co = (COORD){.X = x, .Y = y};
    SetConsoleCursorPosition(consoleHandle, co); // 设置你的光标位置
    printf("%s", ch);                            // 输出字符串
}
/***********************************************************************
 *void MvaddchMiddle(int y, int x, int runway, char ch);
 *
 * 在指定跑道中间y处显示ch
 *
 * 需要传入（字符在的y，屏幕宽度，跑道代号，字符）
 *************************************************************************/
void MvaddchMiddle(int y, int x, int runway, char ch)
{
    switch (runway)
    {
    case 1:
        Mvaddch(3 * y / 4, 7 * x / 18, ch); // 左道
        break;
    case 2:
        Mvaddch(3 * y / 4, x / 2, ch); // 中道
        break;
    case 3:
        Mvaddch(3 * y / 4, 11 * x / 18, ch); // 右道
        break;
    default:
        printf("the MvaddchMiddle have wrong!\n");
        break;
    }
}
/**************************************************************************
 *void Display(int y, int x)
 *
 *显示跑道界限、人物、得分、速度
 *
 *需要传入（屏幕高度，屏幕宽度）;详细参数可在函数内调整
 *
 * ************************************************************************/
void Display(int y, int x, int man, int score, int speed, Obstacle obstacle)
{
    // for (int i = 0; i <= y; i++) // 清屏
    // {
    //     printf("\n");
    // }
    system("cls");

    char CharOfRunway = '|'; // 显示跑道
    MvaddchCol(y, x / 3, CharOfRunway);
    MvaddchCol(y, 4 * x / 9, CharOfRunway);
    MvaddchCol(y, 5 * x / 9, CharOfRunway);
    MvaddchCol(y, 2 * x / 3, CharOfRunway);

    MvaddchMiddle(3 * y / 4, x, man, '*'); // 显示人物

    for (int i = 1; i <= 3; i++) // 显示障碍物
    {
        for (int j = 0; j < 3; j++)
        {
            if (obstacle.Down[i][j] != 0)
            {
                MvaddchMiddle(obstacle.Down[i][j], x, i, 'D');
            }
        }
    }

    MvaddchRow(y - 2, 2, "Score:"); // 显示得分
    printf("%d", score);
    MvaddchRow(y - 3, 2, "Speed:"); // 显示速度
    printf("%d", score);
}

/*****************************************
 *void InitObstacle(Obstacle *obstacle)
 *
 * 初始化obstacle
 ******************************************/
void InitObstacle(Obstacle *obstacle)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            obstacle->Down[i][j] = 0;
        }
    }
}

/*****************************************************
 *void GenerateObstacle(Obstacle *obstacle, int random)
 *
 * 障碍物生成逻辑(缺少判断有路逻辑)
 *
 * 需要传入（障碍物结构体，随机数(未处理)）
 *********************************************************/
void GenerateObstacle(Obstacle *obstacle, int random)
{
    for (int i = 1; i <= 3; i++)
    {
        if (obstacle->Down[i][0] == 0)
        {
            if (random % 17 == 1)
            {
                obstacle->Down[i][0] = 1;
                random = rand();
            }
        }
    }
}

/*****************************************************
 *void MoveObstacle(Obstacle *obstacle)
 *
 *移动障碍物
 *
 *需要传入屏幕高度
 *
 *********************************************************/
void MoveObstacle(Obstacle *obstacle, int y)
{
    for (int i = 1; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (obstacle->Down[i][j] > y - 2)
            {
                obstacle->Down[i][j] = 0;
            }
            if (obstacle->Down[i][j] > 0)
            {
                obstacle->Down[i][j]++;
            }
        }
    }
}