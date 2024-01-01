// 23.12.30
// test for multiple-file optation
// by HHC

#ifndef MyRun
#define MyRun

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

#endif