// 23.12.31
// for homework
//  by HHC
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct node
{
    int sapce;
    int id;
    struct node *next;
} Node;

typedef struct buddy
{
    Node *head;
    Node *tail;
    int total;
} Buddy;

void Initialize(Buddy *buddy, int space);
void InitNode(Node *node);
void Question(Buddy *buddy);
void PutInto(Buddy *buddy, int id, int space);
bool IsEnough(Node *node, int space);
int NeedSpace(int space);
void Divide(Buddy *buddy, int tspace);

int main()
{
    int n = 0, q = 0;
    Buddy buddy;
    scanf("%d%d", &n, &q);
    char ch = getchar();
    if (ch != '\n')
    {
        ch = getchar();
    }

    Initialize(&buddy, n);

    while (q--)
    {
        ch = getchar();
        if (ch == 'Q')
        {
            Question(&buddy);
        }
        else
        {
            int new_id = 0, new_space = -1;
            scanf("%d%d", &new_id, &new_space);
            PutInto(&buddy, new_id, new_space);
        }
        if ((ch = getchar()) != '\n')
        {
            ch = getchar();
        }
    }
    return 0;
}

void Initialize(Buddy *buddy, int space)
{
    buddy->head = malloc(sizeof(Node));
    if (buddy->head == NULL)
    {
        printf("malloc failed\n");
        return;
    }
    InitNode(buddy->head);
    buddy->tail = buddy->head;
    buddy->head->sapce = space;
    buddy->total = 1;
}

void InitNode(Node *node)
{
    node->id = 0;
    node->sapce = 0;
    node->next = NULL;
}

void Question(Buddy *buddy)
{
    printf("%d\n", buddy->total);
    for (Node *p = buddy->head; p != NULL; p = p->next)
    {
        printf("%d ", p->id);
        // printf("%d(SPACE=%d) ", p->id, p->sapce);
    }
    printf("\n");
}

int NeedSpace(int space)
{
    int need = 0;
    while (space > pow(2, need))
    {
        need++;
    }
    return need;
}

bool IsEnough(Node *node, int space)
{
    return space <= NeedSpace(node->sapce);
}

void Divide(Buddy *buddy, int tspace)
{

    for (Node *p = buddy->head; p != NULL; p = p->next)
    {
        if (p->id == 0 && p->sapce > tspace)
        {
            Node *new = malloc(sizeof(Node));
            if (new == NULL)
            {
                printf("malloc failed\n");
                return;
            }
            buddy->total++;
            InitNode(new);
            (p->sapce)--;
            new->sapce = p->sapce;
            new->next = p->next;
            p->next = new;
            return;
        }
    }
    return;
}

void PutInto(Buddy *buddy, int id, int space)
{
    // printf("the space=%d,THE ID=%d", space, id);
    // printf("--NeedSpace=%d--\n", NeedSpace(space));
    for (Node *p = buddy->head; p != NULL; p = p->next)
    {
        if (p->id == 0 && (p->sapce == NeedSpace(space)))
        {
            p->id = id;
            return;
        }
    }
    Divide(buddy, NeedSpace(space));
    PutInto(buddy, id, space);
}
