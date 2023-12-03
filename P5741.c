// 23.11.29
// for practice
// by HHC

#include <stdio.h>
#include <stdlib.h>

#define MAX 12

int main()
{ // initialization
    int n = 0;
    scanf("%d", &n);
    int **score = NULL;
    if ((score = malloc(n * sizeof(*score))) == NULL)
    {
        printf("malloc failed");
        return 0;
    }
    for (int i = 0; i < n; i++)
    {
        if ((*(score + i) = malloc(5 * sizeof(**score))) == NULL)
        {
            printf("malloc failed");
            return 0;
        }
    }
    char **name = NULL;
    if ((name = malloc(n * sizeof(*name))) == NULL)
    {
        printf("malloc failed");
        return 0;
    }
    for (int i = 0; i < n; i++)
    {
        if ((*(name + i) = malloc(MAX * sizeof(**name))) == NULL)
        {
            printf("malloc failed");
            return 0;
        }
    }
    // input n students
    for (int i = 0; i < n; i++)
    {

        scanf("%s", *(name + i)); // have *
        scanf("%d%d%d", *(score + i) + 0, *(score + i) + 1, *(score + i) + 2);
        *(*(score + i) + 3) = *(*(score + i) + 2) + *(*(score + i) + 1) + *(*(score + i) + 0);
    }

    // find and output
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            int flag = 0;
            for (int subject = 0; subject <= 2; subject++)
            {
                if (abs(*(*(score + i) + subject) - *(*(score + j) + subject)) > 5)
                {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0 && abs(*(*(score + i) + 3) - *(*(score + j) + 3)) <= 10)
            {
                printf("%s %s\n", *(name + i), *(name + j)); // both have *
            }
        }
    }

    free(name);
    free(score);

    return 0;
}