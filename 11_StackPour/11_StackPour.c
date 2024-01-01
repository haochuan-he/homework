// 23.12.30
// for test multiple-file opration
// by HHC

// #include "run/run.h"
#include "run/run.h"

#define MAX 100 // 1000012

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