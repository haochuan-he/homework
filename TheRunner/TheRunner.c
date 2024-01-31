// 24.1.28
// for homework
// by HHC

#include <conio.h> // 必须
#include <stdio.h>
#include <windows.h> // 必须
#include <stdlib.h>
#include <time.h>

#define MAN_Y 3.0 / 4 // 人物所处位置的y系数

HANDLE consoleHandle; // 操作控制台（也就是那个黑框框）需要的一个变量
int w, h;             // 高度，宽度，对应 y 和 x

typedef struct Obstacle // 障碍物，数组中1，2，3分别表示左中右道中障碍物y坐标;一列中可以多个
{
    int Down[5][3];

} Obstacle;

void Mvaddch(int y, int x, char ch);
void MvaddchCol(int y, int x, char ch);
void MvaddchRow(int y, int x, char ch);
void MvaddString(int y, int x, char ch[]);
void MvaddchMiddle(int y, int x, int runway, char ch);
void Clear();
void Display(int y, int x, int man, int score, int speed, Obstacle obstacle, int status);
void InitObstacle(Obstacle *obstacle);
void GenerateObstacle(Obstacle *obstacle, int random);
void MoveObstacle(Obstacle *obstacle, int y);
void MoveMan(char ch, int *man, int *status, int *status_cnt);
void Pause(int y, int x, char ch);
void ChangeManStatus(int *status, int *status_cnt);
void HitCheck(int y, int x, Obstacle obstacle, int man, int statsus, int *score);

void GameOver(int score, int y, int x);

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
    int speed = 0, score = 0, man = 2, status = 0, status_cnt = 0;
    // status: 0 for standing, 1 for sliding, 2 for jumping

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
        Display(h, w, man, score, speed, obstacle, status);
        MoveObstacle(&obstacle, h);
        HitCheck(h, w, obstacle, man, status, &score);
        ChangeManStatus(&status, &status_cnt);

        while (kbhit() != 0)
        {                                            // 如果它检测到有键盘敲击，返回非零。没有则返回 0
            char ch = getch();                       // 有键盘敲击，我们获取是哪一个键
            Pause(h, w, ch);                         // 暂停逻辑(ch==' ')
            MoveMan(ch, &man, &status, &status_cnt); // 人物左右移动
            // Sleep(1000);       // 程序暂停 1000 毫秒
        }
        Sleep(100 - speed);
    }

    /************************************************************************************/
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
    for (int row = 0; row < y; row++)
    {
        Mvaddch(row, x, ch);
    }
}

/*********************************************************************
 *void MvaddchRow(int y, int x, char ch);
 *
 *打印一整行填满屏幕的字符ch
 *
 * 需要传入（期望打印的行处于的y，屏幕宽度，字符）
 ********************************************************************/
void MvaddchRow(int y, int x, char ch)
{
    for (int col = 0; col < x; col++)
    {
        Mvaddch(y, col, ch);
    }
}

/*******************************************************************
 *void MvaddString(int y, int x, char ch[])
 *
 *从 x,y处开始打印字符串ch[]
 *
 * 需要传入（期望出现的y坐标，期望出现的x坐标，打印字符串）
 *
 **********************************************************************/
void MvaddString(int y, int x, char ch[])
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
        Mvaddch(y, 7 * x / 18, ch); // 左道
        break;
    case 2:
        Mvaddch(y, x / 2, ch); // 中道
        break;
    case 3:
        Mvaddch(y, 11 * x / 18, ch); // 右道
        break;
    default:
        printf("the MvaddchMiddle have wrong!\n");
        break;
    }
}

/**********************************************************************
 *void Clear();
 *
 * 实现清屏
 ***********************************************************************/
void Clear()
{
    system("cls"); // 启动游戏的时候有几率闪屏
}
/**************************************************************************
 *void Display(int y, int x)
 *
 *显示跑道界限、人物、得分、速度
 *
 *需要传入（屏幕高度，屏幕宽度）;详细参数可在函数内调整
 *
 * ************************************************************************/
void Display(int y, int x, int man, int score, int speed, Obstacle obstacle, int status)
{
    // for (int i = 0; i <= y; i++) // 清屏
    // {
    //     printf("\n");
    // }
    Clear();
    char CharOfRunway = '|'; // 显示跑道
    MvaddchCol(y, x / 3, CharOfRunway);
    MvaddchCol(y, 4 * x / 9, CharOfRunway);
    MvaddchCol(y, 5 * x / 9, CharOfRunway);
    MvaddchCol(y, 2 * x / 3, CharOfRunway);

    MvaddchMiddle(MAN_Y * y, x, man, '*'); // 显示人物

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

    MvaddString(y - 2, 2, "Score:"); // 显示得分
    printf("%d", score);
    MvaddString(y - 3, 2, "Speed:"); // 显示速度
    printf("%d", score);
    MvaddString(MAN_Y * y, 2 * x / 3 + 1, "Status:"); // 显示人物状态
    switch (status)
    {
    case 0:
        printf("standing");
        break;
    case 1:
        printf("sliding");
        break;
    case 2:
        printf("jumping");
        break;
    default:
        printf("display man status wrong!\n");
    }
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
 *void MoveObstacle(Obstacle *obstacle, int y)
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

/*****************************************************
 *void MoveMan(char ch, int *man, int *status, int *status_cnt)
 *
 *根据ch反馈人物移动,1/2/3 代表左中右
 *
 * 需要传入ch
 *****************************************************/
void MoveMan(char ch, int *man, int *status, int *status_cnt)
{
    // 左右移动更换跑道
    if ((ch == 'a' || ch == 'A') && *man != 1)
    {
        *man -= 1;
    }
    else if ((ch == 'd' || ch == 'D') && *man != 3)
    {
        *man += 1;
    }

    // 改变人物状态
    if (ch == 'w' || ch == 'W')
    {
        *status = 2;
        *status_cnt = 5; // 状态保持五帧
    }
    else if (ch == 's' || ch == 'S')
    {
        *status = 1;
        *status_cnt = 5; // 状态保持五帧
    }
}

/******************************************************
 *void Pause(int y, int x, char ch);
 *
 *暂停逻辑，检测到空格时暂停
 *
 *********************************************************/
void Pause(int y, int x, char ch)
{
    if (ch == ' ')
    {
        Clear();
        MvaddchRow(y / 3, x, '-');
        MvaddchRow(2 * y / 3, x, '-');
        MvaddString(y / 3 + 1, x / 2 - 2, "PAUSE");
        MvaddString(2 * y / 3 - 1, x / 2 - 12, "Enter any key to continue......");
        fflush(stdin); // 清空输入流缓存,避免连续按住空格暂停失败
        Sleep(1000);
        fflush(stdin); // 清空输入流缓存,避免连续按住空格暂停失败
        // getchar();     // 需要回车确认，互动差劲
        getch(); // 在conio.h库中，从键盘读取一个字符但不显示在控制台，然后自动添加一个回车。
    }
}

/*******************************************************
 *void ChangeManStatus(int *status, int *status_cnt);
 *
 *检测并改变人物当前状态
 *
 * 需要传入当前状态以及状态计数器
 ***********************************************************/
void ChangeManStatus(int *status, int *status_cnt)
{
    if (*status_cnt == 0)
    {
        *status = 0;
    }
    else
    {
        *status_cnt -= 1;
    }
}

/*******************************************************************
 *void HitCheck(Obstacle obstacle, int *score, int man);
 *
 *检测人物与金币、障碍物等是否接触并产生动作
 *
 *需要传入（障碍物，人物位置(默认3*y/4处),人物状态）
 ****************************************************************/
void HitCheck(int y, int x, Obstacle obstacle, int man, int status, int *score)
{
    // 检测障碍物,判断游戏是否会停止
    for (int i = 1; i <= 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (obstacle.Down[i][j] == ((int)(MAN_Y * y) + 1) && status != 1 && man == i)
            {
                GameOver(*score, y, x);
                return;
            }
        }
    }
}

/***************************************************************
 *void GameOver(int score);
 *
 *完成结算游戏显示，衔接重开和结束程序逻辑
 *
 ***************************************************************/
void GameOver(int score, int y, int x)
{
    Sleep(1000);
    Clear();
    MvaddchRow(y / 3, x, '-');
    MvaddchRow(2 * y / 3, x, '-');
    MvaddString(y / 3 + 1, x / 2 - 4, "Game over!");
    MvaddString(2 * y / 3 - 1, x / 2 - 8, "Your final score:");
    printf("%d", score);
    Sleep(10000); // 需要修改
}