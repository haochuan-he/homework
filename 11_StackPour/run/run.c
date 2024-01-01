// 23.12.30
// test for multiple-file opration
// by HHC

#include "run.h"

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
