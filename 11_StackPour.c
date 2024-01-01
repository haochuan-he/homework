// 23.12.29
// for homework
// by HHC
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX 100 // 1000012

typedef struct node
{
    struct node *last;
    struct node *next;
    int val;
} Node;

typedef struct stack
{
    Node *bottom;
    Node *top;
} Stack;

void Initialize(Stack *stack, int num);
void Print(Stack *stack);
bool IsEmpty(Stack *stack);
Node *go(Node *cur, Node *ptrv);
void Cut(Stack *first, Stack *second);

int main(void)
{
    // initialize
    int n, m;
    scanf("%d%d", &n, &m);
    Stack *all[MAX];
    for (int i = 1; i <= n; i++)
    {
        all[i] = malloc(sizeof(*all[i]));
        if (all[i] == NULL)
        {
            printf("malloc failed \n");
            return 0;
        }
        Initialize(all[i], i);
    }

    // functional part
    while (m--)
    {
        int first = 0, second = 0;
        scanf("%d%d", &first, &second);
        Cut(all[first], all[second]);

        //    for test
        // printf("The %d :\n", m);
        // printf("stack %d :", first);
        // Print(all[first]);
        // printf("stack %d :", second);
        // Print(all[second]);
        // printf("----------------\n\n--------------\n");
    }
    // printf("\n\n");

    // output
    for (int i = 1; i <= n; i++)
    {
        Print(all[i]);
    }
    return 0;
}

void Initialize(Stack *stack, int num)
{
    stack->top = NULL;
    stack->bottom = NULL;

    stack->top = malloc(sizeof(Node));
    if (stack->top == NULL)
    {
        printf("malloc failed\n");
        return;
    }

    stack->top->val = num;
    stack->top->last = NULL;
    stack->top->next = NULL;
    stack->bottom = stack->top;
}

bool IsEmpty(Stack *stack)
{
    return stack->top == NULL;
}
Node *go(Node *cur, Node *ptrv)
{
    if (cur == NULL)
    {
        return NULL;
    }
    else
    {
        return cur->last == ptrv ? cur->next : cur->last;
    }
}

void Cut(Stack *first, Stack *second)
{
    if (IsEmpty(first))
    {
        return;
    }
    if (IsEmpty(second))
    {
        second->bottom = first->top;
        second->top = first->bottom;

        first->bottom = NULL;
        first->top = NULL;
        return;
    }

    if (first->top->last == NULL)
    {
        first->top->last = second->top;
    }
    else
    {
        first->top->next = second->top;
    }

    if (second->top->last == NULL)
    {
        second->top->last = first->top;
    }
    else
    {
        second->top->next = first->top;
    }
    second->top = first->bottom;

    first->bottom = NULL;
    first->top = NULL;
}

void Print(Stack *stack)
{
    if (IsEmpty(stack))
    {
        printf("0\n");
        return;
    }
    Node *cur = stack->bottom, *prev = NULL, *tem = go(cur, prev);
    do
    {
        printf("%d ", cur->val);
        prev = cur;
        cur = tem;
        tem = go(cur, prev);
    } while (cur != NULL);
    // for (Node *cur = stack->bottom, *prev = NULL, *tem = go(cur, prev);
    //      tem != NULL;
    //      prev = cur, cur = tem, tem = go(cur, prev))
    // {
    //     printf("%d ", cur->val);
    // }
    printf("\n");
}

// // 23.12.29
// // for homework
// // by HHC

// #include <stdio.h>
// #include <stdlib.h>
// #include <stdbool.h>

// #define MAX 100 // 1000012

// typedef struct node
// {
//     int val;
//     struct node *next;
// } Unit;

// typedef struct stack
// {
//     Unit *bottom;
//     Unit *top;
// } Stack;

// /*************************************************/
// void Initial(Stack *stack, int num);
// void Print(Stack *stack);
// bool IsEmpty(Stack *stack);
// int pop(Stack *stack);
// void push(Stack *stack, int num);
// /**********************************************/
// int main()
// {
//     Stack *all[MAX];

//     int n, m;
//     scanf("%d%d", &n, &m);

//     // initialize
//     for (int i = 0; i < n; i++)
//     {
//         all[i] = malloc(sizeof(*all[i]));
//         if ((all[i]) == NULL)
//         {
//             printf("malloc failed\n");
//             return 0;
//         }
//         Initial(all[i], i + 1);
//     }

//     // functional part
//     while (m--)
//     {
//         int first = 0, second = 0;
//         scanf("%d%d", &first, &second);
//         first--, second--;
//         while (!IsEmpty(all[first]))
//         {
//             push(all[second], pop(all[first]));
//         }
//         // for test
//         // printf("The %d :\n", m);
//         // printf("stack %d :", 1 + first);
//         // Print(all[first]);
//         // printf("stack %d :", 1 + second);
//         // Print(all[second]);
//         // printf("----------------\n\n--------------");
//     }

//     // output
//     for (int i = 0; i < n; i++)
//     {
//         Print(all[i]);
//     }

//     return 0;
// }
// /***********************************************/

// void Initial(Stack *stack, int num)
// {
//     stack->bottom = NULL;
//     stack->top = NULL;
//     if ((stack->bottom = malloc(sizeof(Unit))) == NULL)
//     {
//         printf("malloc failed \n");
//         return;
//     }
//     stack->top = stack->bottom;
//     stack->top->val = num;
//     stack->bottom->next = NULL;
// }

// void Print(Stack *stack)
// {
//     if (IsEmpty(stack))
//     {
//         printf("0\n");
//         return;
//     }

//     int tem[MAX] = {0};
//     int index = 0;

//     for (Unit *ptr = stack->top; ptr != NULL; ptr = ptr->next)
//     {
//         tem[index++] = ptr->val;
//     }
//     index--;
//     while (index >= 0)
//     {
//         printf("%d ", tem[index]);
//         index--;
//     }

//     printf("\n");
// }

// bool IsEmpty(Stack *stack)
// {
//     return stack->top == NULL;
// }

// int pop(Stack *stack)
// {
//     if (IsEmpty(stack))
//     {
//         printf("pop an empty stack\n");
//         return -1;
//     }

//     Unit *tem = stack->top->next;
//     int out = stack->top->val;
//     free(stack->top);
//     stack->top = tem;

//     return out;
// }

// void push(Stack *stack, int num)
// {
//     Unit *new = malloc(sizeof(*new));
//     if (new == NULL)
//     {
//         printf("malloc failedn\n");
//         return;
//     }

//     new->val = num;
//     new->next = stack->top;
//     stack->top = new;
// }
