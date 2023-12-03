// 23.12.2
// for homework
// by HHC
// 无最后语句分号结尾检查
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 4100 // 4100

int ans[MAX] = {0}; //-1 for \n ;each num for each situation
// char reserved[] = {" const , int , float , double , long , static , void ,\
//  char , extern , return , break , enum , struct , typedef , union , goto "};
// char operator[] = {" + , - , * , / , = , == , != , >= , <= , > , < "};

void process(char old_buffer[], char *begin, char *end, int *index);
void output();
void input(char buffer[], int *index);
int num1(char buffer[], int *index);
int num4(char buffer[], int *index);

int main()
{
    // int flag_fen = 0;
    int index = 0;
    char buffer[MAX];
    memset(buffer, '\0', MAX);

    while (scanf("%s", buffer) != EOF)
    {
        input(buffer, &index);
        // char *position = strchr(buffer, ';'); // if there's no ';' in s, it returns NULL.

        // if (position == NULL)
        // {
        //     // flag_fen = 0;
        //     process(buffer, buffer, buffer + MAX, &index);
        // }
        // else
        // {
        //     // flag_fen = 1;
        //     process(buffer, buffer, position - 1, &index);       // process(s 中分号前的部分);
        //     ans[index++] = -1;                                   // 在输出末尾加个换行;
        //     process(buffer, position + 1, buffer + MAX, &index); // process(s 中分号后的部分);
        //     // if (*(position + 1) != '\0')
        //     // {
        //     //     flag_fen = 0;
        //     // }
        // }
    }
    // if (flag_fen == 0)
    // {
    //     ans[0] = 12;
    // }
    output();

    return 0;
}

void input(char buffer[], int *index)
{
    char *position = strchr(buffer, ';'); // if there's no ';' in s, it returns NULL.

    if (position == NULL)
    {

        process(buffer, buffer, buffer + MAX, index);
    }
    else
    {

        process(buffer, buffer, position - 1, index); // process(s 中分号前的部分);
        ans[(*index)++] = -1;                         // 在输出末尾加个换行;
                                                      // if (*(position + 1) == ';')
                                                      // {
        input(position + 1, index);
        // }
        // else
        // {
        //     process(buffer, position + 1, buffer + MAX, index); // process(s 中分号后的部分);}
        // }
    }
}

void process(char old_buffer[], char *begin, char *end, int *index)
{
    char buffer[MAX];
    memset(buffer, '\0', MAX);
    strncpy(buffer + 1, begin, end - begin + 1);
    buffer[0] = ' ';

    if (buffer[1] == '\0')
    {
        return;
    }

    // printf("%s\n", buffer);//for test

    // // 1-reserve
    if (num1(buffer, index) == 1)
    {
        ans[(*index)++] = 1;
        return;
    }
    // int *num1 = (int *)strstr(reserved, buffer);
    // if (num1 != NULL && isalpha(buffer[1]) && buffer[2] != '\0' && buffer[3] != '\0')
    // {
    //     ans[(*index)++] = 1;
    //     return;
    // }

    // 4-operator
    if (num4(buffer, index) == 1)
    {
        ans[(*index)++] = 4;
        return;
    }
    // int *num4 = (int *)strstr(operator, buffer);
    // if (num4 != NULL && !(buffer[1] == ';' || buffer[1] == ' ' || buffer[1] == '\0'))
    // {
    //     ans[(*index)++] = 4;
    //     return;
    // }

    // 5-variable
    int num5 = 1;
    if (isalpha(buffer[1]) || buffer[1] == '_')
    {
        for (; buffer[num5] != '\0'; num5++)
        {
            if (!(isalnum(buffer[num5]) || isdigit(buffer[num5]) || buffer[num5] == '_'))
            {
                break;
            }
        }
    }
    if (buffer[num5] == '\0' && buffer[1] != '\0')
    {
        ans[(*index)++] = 5;
        return;
    }

    // 2-integer
    int num2 = 1;
    for (; buffer[num2] != '\0'; num2++)
    {
        if (!('0' <= buffer[num2] && buffer[num2] <= '9'))
        {
            break;
        }
    }
    if (buffer[num2] == '\0' && buffer[1] != '\0')
    {
        ans[(*index)++] = 2;
        return;
    }

    // 3-float
    // search for one point
    char *point = buffer + 1;
    for (; *point != '\0'; point++)
    {
        if (*point == '.')
        {
            *point = '0'; // flag and modify
            break;
        }
    }
    point = buffer + 1;
    for (; *point != '\0'; point++)
    {
        if (!('0' <= *point && *point <= '9'))
        {
            break;
        }
    }
    if (*point == '\0' && buffer[1] != '\0')
    {
        ans[(*index)++] = 3;
        return;
    }

    ans[0] = 12;
    (*index)++;

    return;
}

void output()
{
    for (int i = 0; ans[i] != 0; i++)
    {
        switch (ans[i])
        {
        case -1:
            printf("\n");
            break;
        case 1:
            printf("reserved ");
            break;
        case 2:
            printf("integer ");
            break;
        case 3:
            printf("float ");
            break;
        case 4:
            printf("operator ");
            break;
        case 5:
            printf("variable ");
            break;
        case 12:
            printf("Compile Error");
            return;
        default:
            printf("--WRONG--");
            break;
        }
    }
}

// char reserved[] = {" const , int , float , double , long , static , void ,\
//  char , extern , return , break , enum , struct , typedef , union , goto "};
int num1(char buffer[], int *index)
{
    if (strcmp(buffer, " const") == 0 || strcmp(buffer, " int") == 0 || strcmp(buffer, " float") == 0 || strcmp(buffer, " double") == 0 || strcmp(buffer, " long") == 0 ||
        strcmp(buffer, " static") == 0 || strcmp(buffer, " void") == 0 || strcmp(buffer, " char") == 0 || strcmp(buffer, " extern") == 0 || strcmp(buffer, " return") == 0 ||
        strcmp(buffer, " break") == 0 || strcmp(buffer, " enum") == 0 || strcmp(buffer, " struct") == 0 || strcmp(buffer, " typedef") == 0 || strcmp(buffer, " union") == 0 || strcmp(buffer, " goto") == 0)
        return 1;
    return 0;
}

// char operator[] = {" + , - , * , / , = , == , != , >= , <= , > , < "};

int num4(char buffer[], int *index)
{
    if (strcmp(buffer, " +") == 0 || strcmp(buffer, " -") == 0 || strcmp(buffer, " *") == 0 || strcmp(buffer, " /") == 0 || strcmp(buffer, " =") == 0 ||
        strcmp(buffer, " ==") == 0 || strcmp(buffer, " !=") == 0 || strcmp(buffer, " >=") == 0 || strcmp(buffer, " <=") == 0 || strcmp(buffer, " >") == 0 || strcmp(buffer, " <") == 0)
    {
        return 1;
    }
    return 0;
}
