// 23.12.15
// for homework
// by HHC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1012
int sort(int goal[][4], int two, int n, char *nation[MAX]);
int main()
{
    int n = 0, cnt = 0, goal[MAX][4];
    memset(goal, 0, MAX * 4);
    char *nation[MAX];
    for (int i = 0; i < MAX; i++)
    {
        nation[i] = malloc(50 * sizeof *nation[0]);
    }
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%s", nation[i]);
        for (int j = 0; j < 11; j++)
        {
            char rubish[999];
            int tem1, tem2, tem3;
            scanf("%[^ ]%d%d%d", rubish, &tem1, &tem2, &tem3);
            getchar();
            goal[i][1] += tem1;
            goal[i][2] += tem2;
            goal[i][3] += tem3;
        }
    }
    for (int i = 1; i <= 3; i++)
    {
        sort(goal, i, n, nation);
    }
    for (int i = 0; i < MAX; i++)
    {
        free(nation[i]);
    }
    return 0;
}

int sort(int goal[][4], int two, int n, char *nation[MAX])
{
    for (int j = 0; j < n; j++)
    {
        int max = goal[1][two], index = 1;
        for (int i = 0; i < n; i++)
        {
            if (max < goal[i][two])
            {
                max = goal[i][two];
                index = i;
            }
        }
        printf("%s ", nation[index]);
        goal[index][two] = -1;
    }
    printf("\n");
    return 0;
}