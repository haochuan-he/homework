// 23.12.21 && 24.1.1
// for homework && celebrate for the new year!
// by HHC

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct node
{
    char c;
    struct node *prev;
    struct node *next;
    struct node *last_same;
} Node;

typedef struct line
{
    Node *head;
    Node *tail;
    Node *lower;
    Node *upper;
} Line;

char Eat();
void InitLine(Line *line, char ch);
void InitNode(Node *node);
void Print(Line *line, int read);
bool IsLast(Line *line);
void Append(Line *line, char ch);
int DeleteLast(Line *line);
int DeleteUpper(Line *line);
int DeleteLower(Line *line);
void Track(Line *line);

/****************************************************/

int main(void)
{
    int Q = 0;
    scanf("%d", &Q);
    char ch = Eat();

    Line line;
    bool IsFirst = 1;
    // ch = getchar();
    // InitLine(&line, ch);
    while (Q--)
    {
        while ((ch = getchar()) != '\n' && ch != '\r')
        {
            if (IsFirst)
            {
                if (ch == 'm' || ch == 'M')
                {
                    continue;
                }
                // ch = getchar();
                InitLine(&line, ch);
                IsFirst = 0;
                continue;
            }
            if (ch == '?')
            {
                int print = 0;
                scanf("%d", &print);
                Eat();
                // TODO read last several char;
                Print(&line, print);
                break;
            }
            // TODO : add the line and delete when m or M
            if (ch == 'm' && line.tail != NULL)
            {
                IsFirst = DeleteLower(&line);
            }
            else if (ch == 'M' && line.tail != NULL)
            {
                IsFirst = DeleteUpper(&line);
            }
            else if (ch != 'm' && ch != 'M')
            {
                Append(&line, ch);
            }
        }
        if (ch == '\r')
        {
            ch = getchar();
        }
    }

    return 0;
}

/*******************************************************/

char Eat()
{
    char ch = getchar();
    if (ch != '\n')
    {
        ch = getchar();
    }
    return ch;
}

void InitNode(Node *node)
{
    node->c = '!'; // flag for initialize for the node
    node->next = NULL;
    node->prev = NULL;
    node->last_same = NULL;
    return;
}

void Track(Line *line)
{
    if (islower(line->tail->c))
    {

        line->tail->last_same = line->lower;
        line->lower = line->tail;
    }
    else if (isupper(line->tail->c))
    {

        line->tail->last_same = line->upper;
        line->upper = line->tail;
    }
    else
    {
        printf("Track may wrong\n");
    }
}

void InitLine(Line *line, char ch)
{
    line->head = malloc(sizeof(Node));
    if (line->head == NULL)
    {
        printf("malloc failed in InitLine\n");
        return;
    }
    InitNode(line->head);
    line->head->c = ch;
    line->tail = line->head;
    line->lower = line->upper = NULL;
    Track(line);
    return;
}

void Print(Line *line, int print)
{
    Node *ptr = line->tail;
    print--;
    while (print--)
    {
        if (ptr->prev == NULL)
        {
            printf("over print!\n");

            break;
        }
        ptr = ptr->prev;
    }
    for (; ptr != NULL; ptr = ptr->next)
    {
        putchar(ptr->c);
    }
    putchar('\n');
    return;
}

bool IsLast(Line *line)
{
    return line->tail->prev == NULL;
}

void Append(Line *line, char ch)
{
    Node *new = malloc(sizeof(Node));
    if (new == NULL)
    {
        printf("malloc failed in Append\n");
        return;
    }
    InitNode(new);
    new->c = ch;
    new->prev = line->tail;
    line->tail->next = new;
    line->tail = new;

    Track(line);

    return;
}

int DeleteUpper(Line *line)
{
    if (line->upper == NULL)
    {
        return 0;
    }

    int flag = IsLast(line);

    Node *tem = line->upper;

    if (flag == 1)
    {
        free(line->tail);
        line->head = line->tail = NULL;
        line->lower = line->upper = NULL;
    }
    else
    {
        if (tem->prev != NULL)
        {
            tem->prev->next = tem->next;
        }
        else
        {
            line->head = tem->next;
        }

        if (tem->next != NULL)
        {
            tem->next->prev = tem->prev;
        }
        else
        {
            line->tail = tem->prev;
        }
        line->upper = tem->last_same;
        free(tem);
    }

    return flag;
}

int DeleteLower(Line *line)
{
    if (line->lower == NULL)
    {
        return 0;
    }

    int flag = IsLast(line);

    Node *tem = line->lower;

    if (flag == 1)
    {
        free(line->tail);
        line->head = line->tail = NULL;
        line->lower = line->upper = NULL;
    }
    else
    {
        if (tem->prev != NULL)
        {
            tem->prev->next = tem->next;
        }
        else
        {
            line->head = tem->next;
        }

        if (tem->next != NULL)
        {
            tem->next->prev = tem->prev;
        }
        else
        {
            line->tail = tem->prev;
        }
        line->lower = tem->last_same;
        free(tem);
    }

    return flag;
}

// // 23.12.21 && 24.1.1
// // for homework && celebrate for the new year!
// // by HHC

// #include <stdio.h>
// #include <stdlib.h>
// #include <ctype.h>
// #include <stdbool.h>

// typedef struct node
// {
//     char c;
//     struct node *prev;
//     struct node *next;
// } Node;

// typedef struct line
// {
//     Node *head;
//     Node *tail;
// } Line;

// char Eat();
// void InitLine(Line *line, char ch);
// void InitNode(Node *node);
// void Print(Line *line, int read);
// void Append(Line *line, char ch);
// int DeleteLast(Line *line);

// /****************************************************/

// int main(void)
// {
//     int Q = 0;
//     scanf("%d", &Q);
//     char ch = Eat();

//     Line line;
//     bool IsFirst = 1;
//     // ch = getchar();
//     // InitLine(&line, ch);
//     while (Q--)
//     {
//         while ((ch = getchar()) != '\n' && ch != '\r')
//         {
//             if (IsFirst)
//             {
//                 if (ch == 'm' || ch == 'M')
//                 {
//                     continue;
//                 }
//                 // ch = getchar();
//                 InitLine(&line, ch);
//                 IsFirst = 0;
//                 continue;
//             }
//             if (ch == '?')
//             {
//                 int print = 0;
//                 scanf("%d", &print);
//                 Eat();
//                 // TODO read last several char;
//                 Print(&line, print);
//                 break;
//             }
//             // TODO : add the line and delete when m or M
//             if (ch == 'm' && line.tail != NULL && islower(line.tail->c))
//             {
//                 IsFirst = DeleteLast(&line);
//             }
//             else if (ch == 'M' && line.tail != NULL && isupper(line.tail->c))
//             {
//                 IsFirst = DeleteLast(&line);
//             }
//             else if (ch != 'm' && ch != 'M')
//             {
//                 Append(&line, ch);
//             }
//         }
//         if (ch == '\r')
//         {
//             ch = getchar();
//         }
//     }

//     return 0;
// }

// /*******************************************************/

// char Eat()
// {
//     char ch = getchar();
//     if (ch != '\n')
//     {
//         ch = getchar();
//     }
//     return ch;
// }

// void InitNode(Node *node)
// {
//     node->c = '!'; // flag for initialize for the node
//     node->next = NULL;
//     node->prev = NULL;
//     return;
// }

// void InitLine(Line *line, char ch)
// {
//     line->head = malloc(sizeof(Node));
//     if (line->head == NULL)
//     {
//         printf("malloc failed in InitLine\n");
//         return;
//     }
//     InitNode(line->head);
//     line->head->c = ch;
//     line->tail = line->head;
//     return;
// }

// void Print(Line *line, int print)
// {
//     Node *ptr = line->tail;
//     print--;

//     // for test
//     // printf("--");

//     while (print--)
//     {
//         // if (ptr->prev == NULL && print != 1)
//         if (ptr->prev == NULL)
//         {
//             printf("over print!\n");
//             // return;
//             break;
//         }
//         ptr = ptr->prev;
//     }
//     for (; ptr != NULL; ptr = ptr->next)
//     {
//         putchar(ptr->c);
//     }
//     putchar('\n');
//     return;
// }

// void Append(Line *line, char ch)
// {
//     Node *new = malloc(sizeof(Node));
//     if (new == NULL)
//     {
//         printf("malloc failed in Append\n");
//         return;
//     }
//     InitNode(new);
//     new->c = ch;
//     new->prev = line->tail;
//     line->tail->next = new;
//     line->tail = new;
//     return;
// }

// int DeleteLast(Line *line)
// {
//     // if (line->head == line->tail)
//     if (line->tail->prev == NULL)
//     {
//         free(line->head);
//         line->head = NULL;
//         line->tail = NULL;
//         return 1;
//     }
//     line->tail = line->tail->prev;
//     free(line->tail->next);
//     line->tail->next = NULL;

//     return 0;
// }
