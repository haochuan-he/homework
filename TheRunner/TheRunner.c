// 24.1.28
// for homework
// by HHC

#include <conio.h> // 必须
#include <stdio.h>
#include <windows.h> // 必须
#include <stdlib.h>
#include <time.h>

#define MAN_Y 3.0 / 4    // 人物所处位置的y系数
#define CROSS_Y 7.0 / 12 // 丁字路口横向最低处的系数

HANDLE consoleHandle; // 操作控制台（也就是那个黑框框）需要的一个变量
int w, h;             // 高度，宽度，对应 y 和 x

typedef struct Obstacle // 障碍物，数组中1，2，3分别表示左中右道中障碍物y坐标;一列中可以多个
{
    int Down[4][3];
    int Up[4][3];
    int Stop[4][3];
    int Combination[4][3][2]; // 组合障碍【跑道序号】【同一列顺序】【最低坐标；对应status组合序号3-6】
    int Money[4][3][2];       // 【跑道序号】【同一列顺序】【最低坐标；长度】
    int Star[4][3][2];        // 无敌星【跑道序号】【同一列顺序】【y坐标；剩余持续时间】->时间放入[0][0][0]
    int Cross[2];             // 丁字路口【横向最低处y坐标；人的y坐标】

} Obstacle;

void GameStart(int y, int x, int *game_mode);

void Mvaddch(int y, int x, char ch);
void MvaddchCol(int y_begin, int y_end, int x, char ch);
void MvaddchRow(int y, int x_begin, int x_end, char ch);
void MvaddString(int y, int x, char ch[]);
void MvaddchMiddle(int y, int x, int runway, char ch[], int correct);
void Clear();
void Echo(char *ch);
void Input_1(char *ch, char *add, int speed);
void Input_2(char *ch, char *add, int speed);
void InputPart(char *ch, char *add);
int Confirm(int y, int x, char question[]);
void ChangScoreAndSpeed(int *score, int *speed);
void Display(int y, int x, int man, int score, int speed, Obstacle obstacle, int status, int game_mode);
void InitObstacle(Obstacle *obstacle, int y);
void GenerateObstacle(Obstacle *obstacle, int random, int y);
int GenerateObstaclePart(Obstacle obstacle, int i, int j);
void MoveObstacle(Obstacle *obstacle, int y);
void MoveObstaclePart(int *target, int y);
void MoveMan(char ch, int *man, int *status, int *status_cnt, char add, Obstacle *obstacle, int y, int game_mode);
void Pause(int y, int x, char ch);
void ChangeManStatus(int *status, int *status_cnt, Obstacle *obstacle);
int HitCheck(int y, int x, Obstacle *obstacle, int man, int statsus, int *score, int game_mode);

int GameOver(int score, int y, int x);

//
//
//
int main()
{
    while (1)
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
        int speed = 0, score = 0, man = 2, status = 0, status_cnt = 0,
            game_mode = 0, escape = 0;
        // status: 0 for standing, 1 for sliding, 2 for jumping;
        //         3 for sliding & left, 4 for jumping & left
        //         5 for sliding & right , 6 for jumping & right
        // game_mode 1 for God Mode , 0 for normal mode

        Obstacle obstacle;
        InitObstacle(&obstacle, h);
        srand(time(0)); // 以当前时间为随机数生成器的种子
        // printf("Random value on [0,%d]: %d\n", RAND_MAX, random_variable);

        GameStart(h, w, &game_mode);

        /********************************************************************************/

        // 循环控制
        /************************************************************************************/
        while (1 && escape == 0)
        {
            int random_variable = rand();
            char ch = '\0', add = '\0';
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
            // Input_2(&ch, &add, speed);//长按会卡停游戏

            if (ch != '\0')
            {
                Pause(h, w, ch);                                                       // 暂停逻辑(ch==' ')
                MoveMan(ch, &man, &status, &status_cnt, add, &obstacle, h, game_mode); // 人物左右移动
                // Sleep(1000);       // 程序暂停 1000 毫秒
                if (ch == '\e') // Esc结束游戏
                {
                    if (1 == Confirm(h, w, "Are you sure to STOP the game?"))
                    {
                        escape = 1;
                        break;
                    }
                }
            }
            // Sleep(200 - speed);
        }

        /************************************************************************************/
        // 游戏结束，我们要恢复光标显示
        // cci.bVisible = TRUE;                       // 可见
        // SetConsoleCursorInfo(consoleHandle, &cci); // 重新设置

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
 * 开始游戏，选择游戏模式:1 无敌；0正常
 *
 ******************************************************************************/
void GameStart(int y, int x, int *game_mode)
{
    while (1)
    {
        Clear();
        MvaddchRow(y / 3, 0, x, '-');
        MvaddchRow(2 * y / 3, 0, x, '-');
        MvaddString(y / 3 + 1, x / 2 - 4, "THE RUNNER");
        MvaddString(y / 3 + 4, x / 2 - 10, "->Enter 1 for God Mode");
        MvaddString(y / 3 + 5, x / 2 - 10, "->Enter any else key for Noraml Mode");
        MvaddString(y / 3 + 3, x / 2 - 12, "Please chose your game mode:");

        char ch;
        Echo(&ch);
        if (ch == '1')
        {
            if (1 == Confirm(y, x, "Are you sure to chose God Mode?"))
            {
                *game_mode = 1;
                break;
            }
        }
        else if (1 == Confirm(y, x, "Are you sure to chose Normal Mode?"))
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
void MvaddchCol(int y_begin, int y_end, int x, char ch)
{
    for (int row = y_begin; row < y_end; row++)
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
    system("cls"); // 启动游戏的时候有几率闪屏
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
 * void Input_1(char *ch, char *add);
 *void Input_2(char *ch, char *add);
 *void InputPart(char *ch, char *add);
 * 解决组合键输入问题；
 * 1、2是两个不同的输入函数版本，Part用于交换ch和add，
 * 使得ch保持第一输入，且出现组合输入时ch保持WS基础操作
 *
 ************************************************************************/
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
// 从属于Input
void InputPart(char *ch, char *add)
{
    if ((*add == 'w' || *add == 'W' || *add == 's' || *add == 'S') ||
        (*add != '\0' && *ch == '\0')) // 未组合键
    {
        *ch ^= *add ^= *ch ^= *add;
    }
}

/***************************************************************************
 *int Confirm(int y, int x, char question[], char option[]);
 *
 *以固定的格式进行输入确认操作，返回1为确认，返回0为误操作
 *
 **************************************************************************/
int Confirm(int y, int x, char question[])
{
    char ch;
    Clear();
    MvaddchRow(y / 3, 0, x, '-');
    MvaddchRow(2 * y / 3, 0, x, '-');
    MvaddString(y / 2 - 1, x / 2 - 16, question);
    MvaddString(y / 2 + 1, x / 2 - 24, "Please enter 1 to confirm,enter any else key to go back:");
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
 *void Display(int y, int x)
 *
 *显示跑道界限、人物、得分、速度
 *
 *需要传入（屏幕高度，屏幕宽度）;详细参数可在函数内调整
 *
 * ************************************************************************/
void Display(int y, int x, int man, int score, int speed, Obstacle obstacle, int status, int game_mode)
{
    // for (int i = 0; i <= y; i++) // 清屏
    // {
    //     printf("\n");
    // }
    Clear();
    char CharOfRunway = '|'; // 显示跑道
    MvaddchCol(obstacle.Cross[0], y, x / 3, CharOfRunway);
    MvaddchCol(obstacle.Cross[0], y, 4 * x / 9, CharOfRunway);
    MvaddchCol(obstacle.Cross[0], y, 5 * x / 9, CharOfRunway);
    MvaddchCol(obstacle.Cross[0], y, 2 * x / 3, CharOfRunway);

    if (obstacle.Cross[0] > 0)
    {
        MvaddchRow(obstacle.Cross[0], 0, x / 3, '-');
        MvaddchRow(obstacle.Cross[0], 2 * x / 3, x, '-');
        if (obstacle.Cross[0] - y / 3 > 0) // 可以打印上界
        {
            MvaddchRow(obstacle.Cross[0] - y / 3, 0, x, '-');
        }
    }

    for (int i = 1; i <= 3; i++) // 显示障碍物
    {
        for (int j = 0; j < 3; j++)
        {
            if (obstacle.Money[i][j][0] != 0) // 显示金币
            {
                for (int k = 0; k < obstacle.Money[i][j][1] && (obstacle.Money[i][j][0] - k > 0); k++)
                {
                    MvaddchMiddle(obstacle.Money[i][j][0] - k, x, i, "$", 0);
                }
            }
            if (obstacle.Star[i][j][0] != 0)
            {
                MvaddchMiddle(obstacle.Star[i][j][0], x, i, "~", 0); // 无敌星
            }
            if (obstacle.Down[i][j] != 0)
            {
                MvaddchMiddle(obstacle.Down[i][j], x, i, "D", 0);
            }
            if (obstacle.Up[i][j] != 0)
            {
                MvaddchMiddle(obstacle.Up[i][j], x, i, "U", 0);
            }
            if (obstacle.Stop[i][j] != 0)
            {
                MvaddchMiddle(obstacle.Stop[i][j], x, i, "X", 0);
            }
            if (obstacle.Combination[i][j][0] != 0)
            {
                switch (obstacle.Combination[i][j][1])
                {
                case 3:
                    MvaddchMiddle(obstacle.Combination[i][j][0], x, i, "D&L", -1);
                    break;
                case 4:
                    MvaddchMiddle(obstacle.Combination[i][j][0], x, i, "U&L", -1);
                    break;
                case 5:
                    MvaddchMiddle(obstacle.Combination[i][j][0], x, i, "D&R", -1);
                    break;
                case 6:
                    MvaddchMiddle(obstacle.Combination[i][j][0], x, i, "U&R", -1);
                    break;
                default:
                    printf("display conbination obstacles wrong\n");
                    break;
                }
            }
        }
    }

    if (obstacle.Cross[0] == 0)
    {
        MvaddchMiddle(MAN_Y * y, x, man, "*", 0); // 显示人物
    }
    else
    {
        MvaddchMiddle(obstacle.Cross[1], x, man, "*", 0);
    }

    MvaddString(y - 2, 2, "Score:"); // 显示得分
    printf("%d", score);
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
    if (obstacle.Star[0][0][0] > 0)
    {
        MvaddString(y - 6, 2, "Star:"); // 显示无敌星剩余时间
        printf("%d", obstacle.Star[0][0][0]);
    }

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

/*****************************************
 *void InitObstacle(Obstacle *obstacle)
 *
 * 初始化obstacle
 ******************************************/
void InitObstacle(Obstacle *obstacle, int y)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            obstacle->Down[i][j] = 0;
            obstacle->Up[i][j] = 0;
            obstacle->Stop[i][j] = 0;
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
 *void GenerateObstacle(Obstacle *obstacle, int random)
 *
 * 障碍物生成逻辑(缺少判断有路逻辑)
 *
 * 需要传入（障碍物结构体，随机数(未处理)）
 *********************************************************/
void GenerateObstacle(Obstacle *obstacle, int random, int y)
{
    if (random % 101 == 1 && obstacle->Cross[0] == 0)
    {
        obstacle->Cross[0] = 1;
        obstacle->Cross[1] = (int)(MAN_Y * y);
        random = rand() + 31;
    }
    if (obstacle->Cross[0] == 0)
    {
        for (int i = 1; i <= 3; i++)
        {
            if (obstacle->Down[i][0] == 0 && GenerateObstaclePart(*obstacle, i, 0)) // 生成单个down
            {
                if (random % 13 == 1)
                {
                    obstacle->Down[i][0] = 1;
                    random = rand() + 37;
                }
            }
            if (obstacle->Up[i][0] == 0 && GenerateObstaclePart(*obstacle, i, 0)) // 生成单个up
            {
                if (random % 17 == 1)
                {
                    obstacle->Up[i][0] = 1;
                    random = rand() + 213;
                }
            }
            if (obstacle->Stop[i][0] == 0 && GenerateObstaclePart(*obstacle, i, 0)) // 生成单个stop
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
            if (obstacle->Combination[i][0][0] == 0 && GenerateObstaclePart(*obstacle, i, 0)) // 生成单个Combination
            {
                if (random % 43 == 1)
                {
                    random = rand() + 2 + rand();
                    obstacle->Combination[i][0][0] = 1;
                    obstacle->Combination[i][0][1] = (random % 4) + 3;
                }
            }

            if (obstacle->Money[i][0][0] == 0 && GenerateObstaclePart(*obstacle, i, 0)) // 生成money
            {
                if (random % 12 == 1)
                {
                    random = rand() + 5;
                    obstacle->Money[i][0][0] = 1;
                    obstacle->Money[i][0][1] = random % 7;
                }
            }

            if (obstacle->Star[i][0][0] == 0 && GenerateObstaclePart(*obstacle, i, 0)) // 生成单个无敌星
            {
                if (random % 371 == 1)
                {
                    obstacle->Star[i][0][0] = 1;
                    random = rand() + 19;
                }
            }
        }
    }
}
// 从属于GenerateObstacle,逻辑判断附近可以生成障碍物或金币
int GenerateObstaclePart(Obstacle obstacle, int i, int j)
{
    return (obstacle.Down[i][j] == 0 || obstacle.Down[i][j] > 5) &&
           (obstacle.Up[i][j] == 0 || obstacle.Up[i][j] > 5) &&
           (obstacle.Stop[i][j] == 0 || obstacle.Stop[i][j] > 5) &&
           (obstacle.Combination[i][j][0] == 0 || obstacle.Combination[i][j][0] > 5) &&
           (obstacle.Star[i][j][0] == 0 || obstacle.Star[i][j][0] > 5) &&
           (obstacle.Money[i][j][0] == 0 || (obstacle.Money[i][j][0] - obstacle.Money[i][j][1] > 5));
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

/*****************************************************
 *void MoveMan(char ch, int *man, int *status, int *status_cnt)
 *
 *根据ch反馈人物移动,1/2/3 代表左中右
 *
 * 需要传入ch
 *****************************************************/
void MoveMan(char ch, int *man, int *status, int *status_cnt, char add, Obstacle *obstacle, int y, int game_mode)
{

    // 路口移动部分判断
    if (obstacle->Cross[0] > 0 && obstacle->Cross[1] < (int)(CROSS_Y * y))
    {
        if ((ch == 'a' || ch == 'A' || ch == 'd' || ch == 'D') || game_mode == 1)
        {
            obstacle->Cross[0] = 0;
            obstacle->Cross[1] = (int)(MAN_Y * y);
        }
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
    else // 出现组合键
    {

        if (add == 'a' || add == 'A')
        {
            *status += 2;
        }
        else if (add == 'd' || add == 'D')
        {
            *status += 4;
        }
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
        MvaddchRow(y / 3, 0, x, '-');
        MvaddchRow(2 * y / 3, 0, x, '-');
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
    if (obstacle->Star[0][0][0] > 0)
    {
        obstacle->Star[0][0][0] -= 1;
    }
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
int HitCheck(int y, int x, Obstacle *obstacle, int man, int status, int *score, int game_mode)
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
                *score += 5; // 1 $ = 5 scores
            }
            if (obstacle->Star[i][j][0] == (int)(MAN_Y * y) && man == i)
            {
                obstacle->Star[0][0][0] = 60; // 无敌星60帧
            }
            // 撞上障碍物
            if (0 == game_mode && obstacle->Star[0][0][0] == 0)
            {
                if (obstacle->Down[i][j] == ((int)(MAN_Y * y) + 1) && status != 1 && man == i)
                {
                    return 1; // 结束循环控制，启动游戏结算
                }
                if (obstacle->Up[i][j] == ((int)(MAN_Y * y) + 1) && status != 2 && man == i)
                {
                    return 1; // 结束循环控制，启动游戏结算
                }
                if (obstacle->Stop[i][j] == ((int)(MAN_Y * y) + 1) && man == i)
                {
                    return 1; // 结束循环控制，启动游戏结算
                }
                if (obstacle->Combination[i][j][0] == ((int)(MAN_Y * y) + 1) &&
                    status != obstacle->Combination[i][j][1] && man == i)
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
int GameOver(int score, int y, int x)
{
    int control = 0;
    char ch = '9';
    while (1)
    {
        Sleep(1000);
        Clear();
        MvaddchRow(y / 3, 0, x, '-');
        MvaddchRow(2 * y / 3, 0, x, '-');
        MvaddString(y / 3 + 1, x / 2 - 4, "Game over!");
        MvaddString(2 * y / 3 - 1, x / 2 - 8, "Your final score:");
        printf("%d", score);
        MvaddString(2 * y / 3 + 2, x / 2 - 24, "Enter 1 for another round,enter else key to exit:");

        Echo(&ch);
        if ('1' == ch)
        {
            if (1 == Confirm(y, x, "Are you sure to play another round?"))
            {
                control = 1;
                break;
            }
        }
        else if (1 == Confirm(y, x, "Are you sure to EXIT the game?"))
        {
            control = 0;
            break;
        }
    }
    return control;
}