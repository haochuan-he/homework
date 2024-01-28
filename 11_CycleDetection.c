// 24.1.6
// for homework
// by HHC
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100 // 100012
typedef struct node
{
    char name[50];
    int next_index;
} Node;
int Judge(Node *list[]);
int main(void)
{
    int out = 0;
    int n = 0;
    scanf("%d", &n);
    Node *list[MAX];
    for (int i = 0; i < MAX; i++)
    {
        list[i] = NULL;
    }
    for (int i = 1; i <= n; i++)
    {
        list[i] = malloc(sizeof(Node));
        if (list[i] == NULL)
        {
            printf("malloc failed in list[i]\n");
            return 0;
        }
        char name[50];
        int next = -1;
        scanf("%s %d", name, &next);
        strcpy(list[i]->name, name);
        if (1 <= next && next <= n)
        {
            list[i]->next_index = next;
        }
        else
        {
            out = 1;
        }
    }
    if (out == 1)
    {
        printf("-1\n");
        return 0;
    }
    int judge_index = -1;
    if (n > 1)
    {
        judge_index = Judge(list);
    }
    if (judge_index != -1)
    {
        printf("%s", list[judge_index]->name);
    }
    else
    {
        printf("-1\n");
    }
    return 0;
}
int Judge(Node *list[])
{
    Node *slow = list[1];
    Node *fast = list[1];
    do
    {
        slow = list[slow->next_index];
        fast = list[fast->next_index];
        if (fast != NULL)
        {
            fast = list[fast->next_index];
        }
    } while (slow != fast && fast != NULL);
    if (fast != NULL)
    {
        int entry = 1;
        slow = list[1];
        for (; slow != fast;
             slow = list[slow->next_index], fast = list[fast->next_index])
        {
            entry = slow->next_index;
        }
        return entry;
    }
    else
    {
        return -1;
    }
}
// // 24.1.2
// // for homework as well as prepare for final exam
// // by HHC
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #define MAX 25
// #define MAXNODE 100 // 100064

// typedef struct node
// {
//     char name[MAX];
//     struct node *next;
// } Node;

// Node *CreatNode(void);
// void Into(Node *node, char name[], int next_num, Node *all[]);
// Node *FindStart(Node *begin);
// void Shit(Node *node);

// /*********************************************/

// int main()
// {
//     int n = 0;
//     scanf("%d", &n);

//     Node *all[MAXNODE];
//     for (int i = 1; i <= n + 12; i++)
//     {
//         all[i] = CreatNode();
//     }

//     for (int i = 1; i <= n; i++)
//     {
//         int next_num = 0;
//         scanf("%s %d", all[i]->name, &next_num);
//         if (!(1 <= next_num && next_num <= n))
//         {
//             Shit(all[i]);
//         }
//         else
//         {
//             all[i]->next = all[next_num];
//         }
//     }

//     // functional part
//     // if (all[n]->next->name[1] == '!' || all[n]->next->next->name[1] == '!')
//     // {
//     //     printf("-1\n");
//     // }
//     // else
//     // {
//     //     printf("%s", all[n]->next->name);
//     // }

//     Node *start = FindStart(all[1]);
//     if (start == NULL)
//     {
//         printf("-1\n");
//     }
//     else
//     {
//         printf("%s\n", start->name);
//     }
//     return 0;
// }

// /***************************************/

// void Shit(Node *node)
// {
//     memset(node->name, '!', MAX);
//     node->next = NULL;
//     return;
// }

// Node *CreatNode(void)
// {
//     Node *new = malloc(sizeof(Node));
//     if (new == NULL)
//     {
//         printf("malloc failed in CreatNode\n");
//         return NULL;
//     }
//     memset(new->name, '!', MAX);
//     new->next = NULL;
//     return new;
// }

// void Into(Node *node, char name[], int next_num, Node *all[])
// {
//     // node->name = name;
//     node->next = all[next_num];
//     return;
// }

// Node *FindStart(Node *begin)
// {
//     Node *fast = begin;
//     Node *slow = begin;
//     for (; fast != NULL && slow != fast;)
//     {
//         slow = slow->next;
//         fast = fast->next;
//         if (fast != NULL)
//         {
//             fast = fast->next;
//         }
//     }
//     if (fast == NULL)
//     {
//         return NULL;
//     }
//     slow = begin;
//     for (; slow != fast;)
//     {
//         slow = slow->next;
//         fast = fast->next;
//     }

//     return slow;
// }
