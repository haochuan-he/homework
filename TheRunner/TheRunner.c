// 24.1.28
// for homework
// by HHC

#include <conio.h> // 必须
#include <stdio.h>
#include <windows.h> // 必须
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MAN_Y 3.0 / 4    // 人物所处位置的y系数
#define CROSS_Y 7.0 / 12 // 丁字路口横向最低处的系数

HANDLE consoleHandle; // 操作控制台（也就是那个黑框框）需要的一个变量
int w, h, record = 0; // 高度，宽度，对应 y 和 x

typedef struct Obstacle // 障碍物，数组中1，2，3分别表示左中右道中障碍物y坐标;一列中可以多个
{
    int Down[4][3];
    int Up[4][3];
    int Stop[4][3];
    int Combination[4][3][2]; // 组合障碍【跑道序号】【同一列顺序】【最低坐标；对应status组合序号3-6】
    int Money[4][3][2];       // 【跑道序号】【同一列顺序】【最低坐标；长度】
    int Star[4][3][2];        // 无敌星【跑道序号】【同一列顺序】【y坐标；剩余持续时间】->时间放入[0][0][0]
    int Double[4][3];         // 金币翻倍【跑道序号】【同一列序号】存放对应y坐标->时间放入[0][0]
    int Shoes[4][3];          // 跑鞋【跑道序号】【同一列序号】存放对应y坐标->时间放入[0][0]
    int Cross[2];             // 丁字路口【横向最低处y坐标；人的y坐标】

} Obstacle;

void GameStart(int y, int x, int *game_mode);

void Mvaddch(int y, int x, char ch);
void MvaddchCol(int y_begin, int y_end, int x, char ch);
void MvaddchRow(int y, int x_begin, int x_end, char ch);
void MvaddString(int y, int x, char ch[]);
void MvaddchMiddle(int y, int x, int runway, char ch[], int correct);
void Clear();
void Screen(int *w, int *h);
void Echo(char *ch);
void Input_1(char *ch, char *add, int speed);
void Input_2(char *ch, char *add, int speed);
bool Confirm(int y, int x, char question[]);
void ChangScoreAndSpeed(int *score, int *speed);
void Display(int y, int x, int man, int score, int speed,
             Obstacle obstacle, int status, int game_mode);
void InitObstacle(Obstacle *obstacle, int y, bool is_cross);
void GenerateObstacle(Obstacle *obstacle, int random, int y);
void MoveObstacle(Obstacle *obstacle, int y);
void MoveMan(char ch, int *man, int *status, int *status_cnt, char add,
             Obstacle *obstacle, int y, int game_mode);
void Pause(int y, int x, char ch);
void ChangeManStatus(int *status, int *status_cnt, Obstacle *obstacle);
bool HitCheck(int y, int x, Obstacle *obstacle, int man, int statsus, int *score, int game_mode);

bool GameOver(int score, int y, int x);

//
//
//
int main()
{
    while (1)
    {
        /*初始化*****************************************************************************/
        // 显示界面初始化
        consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // 初始化这个操作器
        CONSOLE_SCREEN_BUFFER_INFO csbi;                 // 屏幕的信息
        Screen(&w, &h);

        CONSOLE_CURSOR_INFO cci; // 光标信息
        cci.dwSize = 100;
        cci.bVisible = FALSE;                      // 不可见
        SetConsoleCursorInfo(consoleHandle, &cci); // 将光标特性应用到控制台
                                                   // 游戏里面，如果一直有输入的光标，就有点不好看。我们可以让它不显示
                                                   // 到这里，闪烁的光标就消失了。
        // 游戏数据初始化
        int speed = 0, score = 0, man = 2, status = 0, status_cnt = 0,
            game_mode = 0, escape = 0;
        // status: 0 for standing, 1 for sliding, 2 for jumping;
        //         3 for sliding & left, 4 for jumping & left
        //         5 for sliding & right , 6 for jumping & right
        // game_mode: 1 for God Mode , 0 for normal mode
        Obstacle obstacle;
        InitObstacle(&obstacle, h, 0);
        srand(time(0)); // 以当前时间为随机数生成器的种子
        GameStart(h, w, &game_mode);

        /*循环控制***********************************************************************************/
        while (1 && escape == 0)
        {
            int random_variable = rand();
            char ch = '\0', add = '\0';
            Screen(&w, &h);
            GenerateObstacle(&obstacle, random_variable, h);
            Display(h, w, man, score, speed, obstacle, status, game_mode);
            MoveObstacle(&obstacle, h);
            if (1 == HitCheck(h, w, &obstacle, man, status, &score, game_mode))
            {
                break; // 脱离循环控制，进入游戏结算
            }
            ChangScoreAndSpeed(&score, &speed);
            ChangeManStatus(&status, &status_cnt, &obstacle);
            Input_1(&ch, &add, speed);
            // Input_2(&ch, &add, speed);//长按会卡停游戏,弃用
            Pause(h, w, ch);                                                                       // 暂停逻辑(ch==' ')
            MoveMan(ch, &man, &status, &status_cnt, add, &obstacle, h, game_mode);                 // 人物左右移动
            if (ch == '\e' && 1 == Confirm(h, w, "Are you sure to \e[31;1;3mSTOP\e[0m the game?")) // Esc结束游戏
            {
                escape = 1;
                break;
            }
        }

        /*一轮游戏结束***********************************************************************************/
        if (0 == GameOver(score, h, w)) // 返回0结束整个程序，返回1重开一局游戏
        {
            break;
        }
    }
    return 0;
}
//
//
//

/********************************************************************************
 *void GameStart(int y,int x,int *game_mode);
 *
 * 开始游戏，选择游戏模式:1 无敌(God Mode)；0正常(Normal Mode)
 ******************************************************************************/
void GameStart(int y, int x, int *game_mode)
{
    while (1)
    {
        Clear();
        MvaddchRow(y / 3, 0, x, '-');
        MvaddchRow(2 * y / 3, 0, x, '-');
        // printf("\033[31;1;3m"); // 红色粗斜体
        MvaddString(y / 3 + 1, x / 2 - 4, "\e[31;1;3mTHE RUNNER\e[0m");
        // printf("\033[0m"); // 重置
        MvaddString(y / 3 + 4, x / 2 - 10, "->Enter\e[4m 1 \e[0mfor \e[36;1;3mGod Mode\e[0m");
        MvaddString(y / 3 + 5, x / 2 - 10, "->Enter \e[4many else key\e[0m for \e[36;1;3mNoraml Mode\e[0m");
        MvaddString(y / 3 + 3, x / 2 - 12, "Please chose your game mode:");

        char ch;
        Echo(&ch);
        if ('1' == ch && 1 == Confirm(y, x, "Are you sure to chose \e[36;1;3mGod Mode\e[0m?"))
        {
            *game_mode = 1;
            break;
        }
        else if (1 == Confirm(y, x, "Are you sure to chose \e[36;1;3mNoraml Mode\e[0m?"))
        {
            *game_mode = 0;
            break;
        }
    }
}

/***************************************************************
 * void Mvaddch(int y, int x, char ch)
 *
 *在屏幕上 y, x 的位置打印一个 ch
 *类似地，你可以以这种方式定义一些在某个位置打印字符串的函数
 **************************************************************/
void Mvaddch(int y, int x, char ch)
{
    COORD co = (COORD){.X = x, .Y = y};
    SetConsoleCursorPosition(consoleHandle, co); // 设置你的光标位置
    putchar(ch);                                 // 在这里打印一个字符
}

/*******************************************************************
 *void MvaddchCol(int y_begin, int y_end, int x, char ch)
 *
 *从y_begin到y_end,x处，打印一列ch
 *
 * 需要传入（起始y坐标，终止y坐标，期望出现的x坐标，打印字符）
 **********************************************************************/
void MvaddchCol(int y_begin, int y_end, int x, char ch)
{
    for (int row = y_begin; row < y_end; row++)
    {
        Mvaddch(row, x, ch);
    }
}

/*********************************************************************
 *void MvaddchRow(int y, int x_begin, int x_end, char ch)
 *
 *在y处，从起始x到终止x打印ch
 *
 * 需要传入（期望打印的行处于的y，起始x坐标，终止x坐标，字符）
 ********************************************************************/
void MvaddchRow(int y, int x_begin, int x_end, char ch)
{
    for (int col = x_begin; col < x_end; col++)
    {
        Mvaddch(y, col, ch);
    }
}

/*******************************************************************
 *void MvaddString(int y, int x, char ch[])
 *
 *从 x,y处开始打印字符串ch[];
 *ch[]部分由printf函数实现，可以嵌入ANSI转义序列
 *
 * 需要传入（期望出现的y坐标，期望出现的x坐标，要打印字符串）
 **********************************************************************/
void MvaddString(int y, int x, char ch[])
{
    COORD co = (COORD){.X = x, .Y = y};
    SetConsoleCursorPosition(consoleHandle, co); // 设置你的光标位置
    printf("%s", ch);                            // 输出字符串
}

/***********************************************************************
 *void MvaddchMiddle(int y, int x, int runway, char ch[], int correct)
 *
 * 在指定跑道中间y处显示ch[]
 *
 * 需要传入（字符在的y，屏幕宽度，跑道代号，字符串，横向偏移修正量）
 *
 * 修正量为负数左偏，为正数右偏，偏移单位数为abs(correct)
 *************************************************************************/
void MvaddchMiddle(int y, int x, int runway, char ch[], int correct)
{
    switch (runway)
    {
    case 1:
        MvaddString(y, 7 * x / 18 + correct, ch); // 左道
        break;
    case 2:
        MvaddString(y, x / 2 + correct, ch); // 中道
        break;
    case 3:
        MvaddString(y, 11 * x / 18 + correct, ch); // 右道
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
    system("cls"); // 启动游戏和通过路口的时候有几率闪屏
    // printf("\033[2J"); // 可以清屏,但会滚动屏幕
    // gotoxy(0, 100); // 我的库里怎么没有？？
}

/**********************************************************************
 *void Screen(int *w, int *h);
 *
 * 检测当前屏幕的宽和高，并存入w,h
 ************************************************************************/
void Screen(int *w, int *h)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;                  // 屏幕的信息
    GetConsoleScreenBufferInfo(consoleHandle, &csbi); // 获取屏幕信息
    *w = csbi.dwSize.X;
    *h = csbi.dwSize.Y;
}

/**********************************************************************
 *void Echo(char *ch);
 *
 * 实现输入并回显一个字符ch
 ***********************************************************************/
void Echo(char *ch)
{
    CONSOLE_CURSOR_INFO cci; // 光标信息
    cci.dwSize = 100;
    cci.bVisible = TRUE;                       // 可见
    SetConsoleCursorInfo(consoleHandle, &cci); // 重新设置

    fflush(stdin);
    Sleep(1000); // 需要修改
    fflush(stdin);
    *ch = getch();
    putchar(*ch);
    Sleep(500); // 需要修改

    cci.bVisible = FALSE;                      // 不可见
    SetConsoleCursorInfo(consoleHandle, &cci); // 将光标特性应用到控制台
}

/************************************************************************
 * void Input_1(char *ch, char *add, int speed);
 *void Input_2(char *ch, char *add, int speed);
 *void InputPart(char *ch, char *add);
 * 解决组合键输入问题；
 * 1、2是两个不同的输入函数版本，Part用于交换ch和add，
 * 使得ch保持第一输入，且出现组合输入时ch保持WS基础操作
 *
 ************************************************************************/
// 从属于Input
void InputPart(char *ch, char *add)
{
    if ((*add == 'w' || *add == 'W' || *add == 's' || *add == 'S') ||
        (*add != '\0' && *ch == '\0')) // 未组合键
    {
        *ch ^= *add ^= *ch ^= *add;
    }
}
//
void Input_1(char *ch, char *add, int speed)
{
    if (kbhit() != 0)
    {
        *ch = getch();
    }
    if (kbhit() != 0)
    {
        *add = getch();
    }
    Sleep(200 - speed);
    InputPart(ch, add);
}
void Input_2(char *ch, char *add, int speed)
{
    int sleep = 0;
    while (kbhit() != 0)
    {
        *add = *ch;
        *ch = getch();
        Sleep(200 - speed);
        sleep = 1;
    }
    if (sleep == 0)
    {
        Sleep(200 - speed);
    }
    InputPart(ch, add);
}

/***************************************************************************
 *bool Confirm(int y, int x, char question[]);
 *
 *以固定的格式进行输入确认操作，返回1为确认，返回0为误操作;
 *question由printf实现，可以嵌入ANSI转义序列
 **************************************************************************/
bool Confirm(int y, int x, char question[])
{
    char ch;
    Clear();
    MvaddchRow(y / 3, 0, x, '-');
    MvaddchRow(2 * y / 3, 0, x, '-');
    MvaddString(y / 2 - 1, x / 2 - 16, question);
    MvaddString(y / 2 + 1, x / 2 - 24, "Please enter\e[4m 1 \e[0mto \e[33;3mconfirm\e[0m,"
                                       "enter \e[4many else key\e[0m to \e[33;3mgo back\e[0m:");
    Echo(&ch);
    return '1' == ch;
}

/***************************************************
 *void ChangScoreAndSpeed(int *score, int *speed);
 *
 * 控制得分和速度之间关系（可增加得分阶段提示）
 *
 ******************************************************/
void ChangScoreAndSpeed(int *score, int *speed)
{
    *score += 1;
    if (*score < 1000)
    {
        *speed = 10 + *score * 9 / 100;
    }
    else if (1000 <= *score && *score < 5000)
    {
        *speed = 100 + (*score - 1000) / 80;
    }
    else
    {
        *speed = 150;
    }
}

/**************************************************************************
 *void Display(int y, int x, int man, int score, int speed,
 *屏幕高，屏幕宽，人物所在跑道序号，得分，速度
  Obstacle obstacle, int status, int game_mode)
 *障碍物集合，人物状态，状态计数器,游戏模式
 *
 *完成游戏进行时所有显示工作
 *
 *详细参数可在函数内调整
 *
 * ************************************************************************/
// 从属于Display
void DisplayRunwayAndCross(int y, int x, Obstacle obstacle)
{
    char CharOfRunway = '|'; // 显示跑道
    MvaddchCol(obstacle.Cross[0] + 1, y, x / 3, CharOfRunway);
    MvaddchCol(obstacle.Cross[0] + 1, y, 4 * x / 9, CharOfRunway);
    MvaddchCol(obstacle.Cross[0] + 1, y, 5 * x / 9, CharOfRunway);
    MvaddchCol(obstacle.Cross[0] + 1, y, 2 * x / 3, CharOfRunway);

    if (obstacle.Cross[0] > 0) // 显示路口
    {
        MvaddchRow(obstacle.Cross[0], 0, x / 3, '-');
        MvaddchRow(obstacle.Cross[0], 2 * x / 3, x, '-');
        if (obstacle.Cross[0] - y / 9 > 0)
        {
            MvaddchRow(obstacle.Cross[0] - y / 9, 0, x / 3, '-');
            MvaddchRow(obstacle.Cross[0] - y / 9, 2 * x / 3, x, '-');
            MvaddchMiddle(obstacle.Cross[0] - y / 9, x, 2, "\e[32;1m<--  -->\e[0m", -4);
        }
        if (obstacle.Cross[0] - 2 * y / 9 > 0)
        {
            MvaddchRow(obstacle.Cross[0] - 2 * y / 9, 0, x / 3, '-');
            MvaddchRow(obstacle.Cross[0] - 2 * y / 9, 2 * x / 3, x, '-');
        }
        if (obstacle.Cross[0] - y / 3 > 0) // 可以打印上界
        {
            MvaddchRow(obstacle.Cross[0] - y / 3, 0, x, '-');
        }
    }
}
void DisplayPorp(int target, int x, int runway, char ch[])
{ // 显示道具
    if (target != 0)
    {
        MvaddchMiddle(target, x, runway, ch, 0);
    }
}
void DisplayObstacle(int target, int x, int runway, char down_line[], char up_line[])
{
    // 显示单个障碍
    if (target != 0)
    {
        MvaddchMiddle(target, x, runway, down_line, 0);
        MvaddchMiddle(target + 1, x, runway, up_line, 0);
    }
}
void DisplayObstacleCombination(int x, int i, int j, Obstacle obstacle)
{
    // 显示组合障碍
    if (obstacle.Combination[i][j][0] != 0)
    {
        switch (obstacle.Combination[i][j][1])
        {
        case 3:
            MvaddchMiddle(obstacle.Combination[i][j][0] - 1, x, i, "|", -3); // D&L
            MvaddchMiddle(obstacle.Combination[i][j][0], x, i, "v & <--", -3);
            break;
        case 4:
            MvaddchMiddle(obstacle.Combination[i][j][0] - 1, x, i, "^", -3); // U&L
            MvaddchMiddle(obstacle.Combination[i][j][0], x, i, "| & <--", -3);
            break;
        case 5:
            MvaddchMiddle(obstacle.Combination[i][j][0] - 1, x, i, "|", -3); // D&R
            MvaddchMiddle(obstacle.Combination[i][j][0], x, i, "v & -->", -3);
            break;
        case 6:
            MvaddchMiddle(obstacle.Combination[i][j][0] - 1, x, i, "^", -3); // U&R
            MvaddchMiddle(obstacle.Combination[i][j][0], x, i, "| & -->", -3);
            break;
        default:
            printf("display conbination obstacles wrong\n");
            break;
        }
    }
}
void DisplayPorpRestTime(int target, int y, char ch[])
{ // 显示道具剩余时间
    if (target > 0)
    {
        printf("\033[35;1m"); // 洋红色
        MvaddString(y, 2, ch);
        printf("%d", target);
        printf("\033[0m");
    }
}
void DisplayManStatus(int y, int x, int status)
{ // 显示人物状态
    MvaddString(MAN_Y * y, 2 * x / 3 + 2, "Status:");
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
    case 3:
        printf("sliding & left");
        break;
    case 4:
        printf("jumping & left");
        break;
    case 5:
        printf("sliding & right");
        break;
    case 6:
        printf("jumping & right");
        break;
    default:
        printf("display man status wrong!\n");
    }
}
//
void Display(int y, int x, int man, int score, int speed,
             Obstacle obstacle, int status, int game_mode)
{
    Clear();
    DisplayRunwayAndCross(y, x, obstacle); // 显示跑道和路口

    for (int i = 1; i <= 3; i++) // 显示障碍物
    {
        for (int j = 0; j < 3; j++)
        {
            if (obstacle.Money[i][j][0] != 0) // 显示金币:黄色
            {
                for (int k = 0; k < obstacle.Money[i][j][1] && (obstacle.Money[i][j][0] - k > 0); k++)
                {
                    MvaddchMiddle(obstacle.Money[i][j][0] - k, x, i, "\e[33m$", 0);
                }
            }
            printf("\033[35m");                             // 显示道具:洋红色
            DisplayPorp(obstacle.Star[i][j][0], x, i, "*"); // 显示无敌星
            DisplayPorp(obstacle.Double[i][j], x, i, "x2"); // 显示金币翻倍
            DisplayPorp(obstacle.Shoes[i][j], x, i, "!");   // 显示跑鞋

            printf("\033[36m");                                                    // 显示障碍物:青色
            DisplayObstacle(obstacle.Down[i][j], x, i, "|", "v");                  // Down
            DisplayObstacle(obstacle.Up[i][j], x, i, "^", "|");                    // Up
            DisplayObstacle(obstacle.Stop[i][j], x, i, "\0", "\033[31mX\033[36m"); // Stop:红色

            DisplayObstacleCombination(x, i, j, obstacle); // 显示组合障碍物
        }
    }

    printf("\033[32;1;4m"); // 绿色、粗体、下划线
    if (obstacle.Cross[0] == 0)
    {
        MvaddchMiddle(MAN_Y * y, x, man, "*", 0); // 显示人物
    }
    else
    {
        MvaddchMiddle(obstacle.Cross[1], x, man, "*", 0);
    }
    printf("\033[0m"); // 重置

    MvaddString(y - 2, 2, "Score:"); // 显示得分
    printf("%d", score);
    if (score > record && record > 0)
    {
        printf(" \e[33;3mNew Record!\e[0m");
    }

    MvaddString(y - 3, 2, "Speed:"); // 显示速度
    printf("%d", speed);

    MvaddString(y - 4, 2, "Game Mode:"); // 显示游戏模式
    if (game_mode == 0)
    {
        printf("Normal");
    }
    else
    {
        printf("God");
    }

    DisplayPorpRestTime(obstacle.Star[0][0][0], y - 6, "Star:"); // 显示道具剩余时间：洋红色
    DisplayPorpRestTime(obstacle.Double[0][0], y - 7, "Money Double:");
    DisplayPorpRestTime(obstacle.Shoes[0][0], y - 8, "Shoes:");

    DisplayManStatus(y, x, status); // 显示人物状态
}

/*****************************************
 *void InitObstacle(Obstacle *obstacle, int y, bool is_cross)
 *
 * 初始化obstacle
 *
 * 需要传入（障碍物集合，屏幕高度，是否是路口）
 ******************************************/
void InitObstacle(Obstacle *obstacle, int y, bool is_cross)
{
    for (int i = 0 + is_cross; i < 4; i++) //
    {
        for (int j = 0; j < 3; j++)
        {
            obstacle->Down[i][j] = 0;
            obstacle->Up[i][j] = 0;
            obstacle->Stop[i][j] = 0;
            obstacle->Double[i][j] = 0;
            obstacle->Shoes[i][j] = 0;
            for (int k = 0; k < 2; k++)
            {
                obstacle->Money[i][j][k] = 0;
                obstacle->Star[i][j][k] = 0;
                obstacle->Combination[i][j][k] = 0;
            }
        }
    }
    obstacle->Cross[0] = 0;
    obstacle->Cross[1] = (int)(MAN_Y * y);
}

/*****************************************************
 *void GenerateObstacle(Obstacle *obstacle, int random, int y)
 *
 * 障碍物生成逻辑
 *
 * 需要传入（障碍物结构体，随机数(未处理),屏幕高度 ）
 *********************************************************/
// 从属于GenerateObstacle
bool GenerateObstacleAllow(Obstacle obstacle, int i, int j)
{ // 逻辑判断附近可以生成障碍物或金币
    return (obstacle.Down[i][j] == 0 || obstacle.Down[i][j] > 5) &&
           (obstacle.Up[i][j] == 0 || obstacle.Up[i][j] > 5) &&
           (obstacle.Stop[i][j] == 0 || obstacle.Stop[i][j] > 5) &&
           (obstacle.Combination[i][j][0] == 0 || obstacle.Combination[i][j][0] > 5) &&
           (obstacle.Star[i][j][0] == 0 || obstacle.Star[i][j][0] > 5) &&
           (obstacle.Double[i][j] == 0 || obstacle.Double[i][j] > 5) &&
           (obstacle.Shoes[i][j] == 0 || obstacle.Shoes[i][j] > 5) &&
           (obstacle.Money[i][j][0] == 0 || (obstacle.Money[i][j][0] - obstacle.Money[i][j][1] > 5));
}
void GenerateObstaclePart(int *target, int *random, int condition, int change, Obstacle *obstacle, int runway)
{
    if (*target == 0 && GenerateObstacleAllow(*obstacle, runway, 0)) // 生成单个目标物
    {
        if (*random % condition == 1)
        {
            *target = 1;
            *random = rand() + change;
        }
    }
}
//
void GenerateObstacle(Obstacle *obstacle, int random, int y)
{
    if (random % 183 == 1 && obstacle->Cross[0] == 0)
    {
        obstacle->Cross[0] = 1;
        obstacle->Cross[1] = (int)(MAN_Y * y);
        random = rand() + 31;
    }
    if (obstacle->Cross[0] == 0)
    {
        for (int i = 1; i <= 3; i++)
        {
            GenerateObstaclePart(&obstacle->Down[i][0], &random, 13, 37, obstacle, i); // 生成单个down
            GenerateObstaclePart(&obstacle->Up[i][0], &random, 17, 213, obstacle, i);  // 生成单个up
            if (obstacle->Stop[i][0] == 0 && GenerateObstacleAllow(*obstacle, i, 0))   // 生成单个stop
            {
                if (!(i == 3 && ((obstacle->Stop[1][0] != 0 && obstacle->Stop[2][0] != 0) ||
                                 (abs(obstacle->Stop[1][0] - obstacle->Stop[2][0]) < 5))))
                {
                    if (random % 11 == 1)
                    {
                        obstacle->Stop[i][0] = 1;
                        random = rand() + 7;
                    }
                }
            }
            if (obstacle->Combination[i][0][0] == 0 && GenerateObstacleAllow(*obstacle, i, 0)) // 生成单个Combination
            {
                if (random % 43 == 1)
                {
                    random = rand() + 2 + rand();
                    obstacle->Combination[i][0][0] = 1;
                    obstacle->Combination[i][0][1] = (random % 4) + 3;
                }
            }

            if (obstacle->Money[i][0][0] == 0 && GenerateObstacleAllow(*obstacle, i, 0)) // 生成money
            {
                if (random % 12 == 1)
                {
                    random = rand() + 5;
                    obstacle->Money[i][0][0] = 1;
                    obstacle->Money[i][0][1] = random % 7;
                }
            }
            GenerateObstaclePart(&obstacle->Star[i][0][0], &random, 171, 19, obstacle, i); // 生成单个无敌星
            GenerateObstaclePart(&obstacle->Double[i][0], &random, 135, 43, obstacle, i);  // 生成单个金币翻倍
            GenerateObstaclePart(&obstacle->Shoes[i][0], &random, 143, 91, obstacle, i);   // 生成单个跑鞋
        }
    }
}

/*****************************************************
 *void MoveObstacle(Obstacle *obstacle, int y)
 *
 *移动障碍物
 *
 *需要传入(障碍物，屏幕高度)
 *********************************************************/
// 从属于MoveObstacle
void MoveObstaclePart(int *target, int y)
{
    if (*target > y - 2)
    {
        *target = 0;
    }
    if (*target > 0)
    {
        *target += 1;
    }
}
//
void MoveObstacle(Obstacle *obstacle, int y)
{
    if (obstacle->Cross[0] > 0)
    {
        if (obstacle->Cross[0] < (int)(CROSS_Y * y))
        {
            obstacle->Cross[0] += 1;
        }
        else
        {
            obstacle->Cross[1] -= 1;
            return; // 人移动，则其他图标都不移动了
        }
    }
    for (int i = 1; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // 移动显示的图标
            MoveObstaclePart(&obstacle->Down[i][j], y);
            MoveObstaclePart(&obstacle->Up[i][j], y);
            MoveObstaclePart(&obstacle->Stop[i][j], y);
            MoveObstaclePart(&obstacle->Star[i][j][0], y);
            MoveObstaclePart(&obstacle->Double[i][j], y);
            MoveObstaclePart(&obstacle->Shoes[i][j], y);
            MoveObstaclePart(&obstacle->Combination[i][j][0], y);

            if (obstacle->Money[i][j][0] > 0)
            {
                obstacle->Money[i][j][0] += 1;
                if (obstacle->Money[i][j][0] > y - 2)
                {
                    obstacle->Money[i][j][0] -= 1;
                    obstacle->Money[i][j][1] -= 1;
                }
                if (obstacle->Money[i][j][1] == 0)
                {
                    obstacle->Money[i][j][0] = 0;
                }
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
// 从属于MoveMan
void MoveManPart(int *status, int enable, int *status_cnt, Obstacle *obstacle)
{
    *status = enable;
    *status_cnt = 5; // 状态保持五帧
    if (obstacle->Shoes[0][0] > 0)
    {
        *status_cnt = 5; // 状态保持5+5=10
    }
}
//
void MoveMan(char ch, int *man, int *status, int *status_cnt, char add, Obstacle *obstacle, int y, int game_mode)
{
    // 路口移动部分判断
    if (obstacle->Cross[0] > 0 && obstacle->Cross[1] < (int)(CROSS_Y * y))
    {
        if ((ch == 'a' || ch == 'A' || ch == 'd' || ch == 'D') || game_mode == 1)
        {
            InitObstacle(obstacle, y, 1);
        }
    }
    // 改变人物状态
    if (ch == 'w' || ch == 'W')
    {
        MoveManPart(status, 2, status_cnt, obstacle);
    }
    else if (ch == 's' || ch == 'S')
    {
        MoveManPart(status, 1, status_cnt, obstacle);
    }
    if (add == '\0') // 未组合键
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
    }
    else if (add == 'a' || add == 'A') // 出现组合键
    {
        *status += 2;
    }
    else if (add == 'd' || add == 'D')
    {
        *status += 4;
    }
}

/******************************************************
 *void Pause(int y, int x, char ch);
 *
 *暂停逻辑，检测到空格时暂停
 *********************************************************/
void Pause(int y, int x, char ch)
{
    if (ch == ' ')
    {
        Clear();
        MvaddchRow(y / 3, 0, x, '-');
        MvaddchRow(2 * y / 3, 0, x, '-');
        MvaddString(y / 3 + 1, x / 2 - 2, "\e[3;33mPAUSE\e[0m");
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
// 从属于ChangeManStatus
void ChangeManStatusPart(int *target)
{
    if (*target > 0)
    {
        *target -= 1;
    }
}
//
void ChangeManStatus(int *status, int *status_cnt, Obstacle *obstacle)
{
    // 改变人物动作
    if (*status_cnt == 0)
    {
        *status = 0;
    }
    else
    {
        *status_cnt -= 1;
    }
    // 改变道具有效时间
    ChangeManStatusPart(&obstacle->Star[0][0][0]);
    ChangeManStatusPart(&obstacle->Double[0][0]);
    ChangeManStatusPart(&obstacle->Shoes[0][0]);
}

/*******************************************************************
 *int  HitCheck(Obstacle obstacle, int *score, int man);
 *
 *检测人物与金币、障碍物等是否接触并产生动作;
 *
 *返回0正常运行，返回1启动游戏结算
 *
 *需要传入（障碍物，人物位置(默认3*y/4处),人物状态）
 ****************************************************************/
bool HitCheck(int y, int x, Obstacle *obstacle, int man, int status, int *score, int game_mode)
{
    // 检测障碍物,判断游戏是否会停止
    for (int i = 1; i <= 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // 拾取金币或道具
            if (obstacle->Money[i][j][0] >= (int)(MAN_Y * y) &&
                (int)(MAN_Y * y) >= obstacle->Money[i][j][0] - obstacle->Money[i][j][1])
            {
                *score += 5 * (1 + obstacle->Double[0][0] > 0); // 1 $ = 5(+5) scores
            }
            if (obstacle->Star[i][j][0] == (int)(MAN_Y * y) && man == i)
            {
                obstacle->Star[0][0][0] = 60; // 无敌星60帧
            }
            if (obstacle->Double[i][j] == (int)(MAN_Y * y) && man == i)
            {
                obstacle->Double[0][0] = 180; // 金币翻倍180 帧
            }
            if (obstacle->Shoes[i][j] == (int)(MAN_Y * y) && man == i)
            {
                obstacle->Shoes[0][0] = 100; // 金币翻倍100 帧
            }
            // 撞上障碍物
            if (0 == game_mode && obstacle->Star[0][0][0] == 0)
            {
                if ((obstacle->Down[i][j] == ((int)(MAN_Y * y) + 1) && status != 1 && man == i) ||
                    (obstacle->Up[i][j] == ((int)(MAN_Y * y) + 1) && status != 2 && man == i) ||
                    (obstacle->Stop[i][j] == ((int)(MAN_Y * y) + 1) && man == i) ||
                    ((obstacle->Combination[i][j][0] == ((int)(MAN_Y * y) + 1) &&
                      status != obstacle->Combination[i][j][1] && man == i)))
                {
                    return 1; // 结束循环控制，启动游戏结算
                }
            }
        }
    }
    if (obstacle->Cross[0] > 0 && obstacle->Cross[1] <= (int)(y / 4))
    {
        return 1; // 结束游戏
        // 转入路口部分在MoveMan实现
    }
    return 0; // 正常运行
}

/***************************************************************
 *void GameOver(int score);
 *
 *完成结算游戏显示，衔接重开和结束程序逻辑
 *
 * 返回一个控制值，值为0结束整个程序，值为1重开游戏
 ***************************************************************/
bool GameOver(int score, int y, int x)
{
    int control = 0;
    char ch = '9';
    while (1)
    {
        Sleep(1000);
        Clear();
        MvaddchRow(y / 3, 0, x, '-');
        MvaddchRow(2 * y / 3, 0, x, '-');
        MvaddString(y / 3 + 1, x / 2 - 4, "\e[31;1;3mGame over!\e[0m");
        MvaddString(2 * y / 3 - 3, x / 2 - 8, "Your final score:");
        printf("\e[36;1;4m%d\e[0m", score);
        if (score > record)
        {
            if (record > 0)
            {
                MvaddString(2 * y / 3 - 2, x / 2 - 6, "\e[33;3m Breaking Record!\e[0m");
            }
            record = score;
        }
        else
        {
            MvaddString(2 * y / 3 - 3, x / 2 - 8, "\e[33;3m Your Best Record:");
            printf("%d\e[0m", record);
        }
        MvaddString(2 * y / 3 + 2, x / 2 - 24, "Enter\e[4m 1 \e[0mfor \e[33;3manother round\e[0m,"
                                               "enter \e[4many else key\e[0m to \e[33;3mexit\e[0m:");

        Echo(&ch);
        if ('1' == ch)
        {
            if (1 == Confirm(y, x, "Are you sure to \e[33;3mplay another round\e[0m?"))
            {
                control = 1;
                break;
            }
        }
        else if (1 == Confirm(y, x, "Are you sure to \e[31;1;3mEXIT\e[0m the game?"))
        {
            control = 0;
            break;
        }
    }
    return control;
}