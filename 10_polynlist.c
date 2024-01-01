// 23.12.16
// for homework
// by HHC

#include <stdio.h>

#define MAX 2001200
#define Max(a, b) (a > b ? a : b)
#define abv(a) (a >= 0 ? a : -a)

int Print(int ans[], int max, char name[]);
int Add(int P1[], int P2[], int max, char name[]);
int Subtract(int P1[], int P2[], int max, char name[]);
int Multiply(int P1[], int P2[], int max, char name[]);

int main()
{
    // initialization
    int p1 = 0, p2 = 0, P1[MAX] = {0}, P2[MAX] = {0};
    scanf("%d%d", &p1, &p2);
    char name[20];
    scanf("%s", name);
    for (int i = p1; i >= 0; i--)
    {
        scanf("%d", &P1[i]);
    }
    for (int i = p2; i >= 0; i--)
    {
        scanf("%d", &P2[i]);
    }

    Add(P1, P2, Max(p1, p2), name);
    Subtract(P1, P2, Max(p1, p2), name);
    Multiply(P1, P2, Max(p1, p2), name);
    return 0;
}

int Multiply(int P1[], int P2[], int max, char name[])
{
    int ans[MAX] = {0};
    for (int i = 0; i < max + 12; i++)
    {
        for (int j = 0; j < max + 12; j++)
        {
            ans[i + j] += P1[i] * P2[j];
        }
    }
    Print(ans, max, name);
    return 0;
}

int Subtract(int P1[], int P2[], int max, char name[])
{
    int ans[MAX] = {0};
    for (int i = 0; i < max + 12; i++)
    {
        ans[i] = P1[i] - P2[i];
    }
    Print(ans, max, name);
    return 0;
}

int Add(int P1[], int P2[], int max, char name[])
{
    int ans[MAX] = {0};
    for (int i = 0; i < max + 12; i++)
    {
        ans[i] = P1[i] + P2[i];
    }
    Print(ans, max, name);
    return 0;
}

int Print(int ans[], int max, char name[])
{
    int first = 0, have_p = 0;
    for (int i = max * 2 + 1200; i >= 0; i--)
    {
        if (ans[i] != 0)
        {
            have_p = 1;
            if (first == 1)
            {
                if (ans[i] > 0)
                {
                    printf("+");
                }
            }
            if (ans[i] < 0) // 10 to 80
            {
                printf("-");
            }
            first = 1;
            if (i > 1)
            {
                if (abv(ans[i]) == 1)
                {
                    printf("%s^%d", name, i);
                }
                else
                {
                    printf("%d%s^%d", abv(ans[i]), name, i);
                }
            }
            else if (i == 1)
            {
                if (abv(ans[i]) == 1)
                {
                    printf("%s", name);
                }
                else
                {
                    printf("%d%s", abv(ans[i]), name);
                }
            }
            else if (i == 0)
            {
                printf("%d", abv(ans[i]));
            }
        }
    }
    if (have_p == 0)
    {
        printf("0");
    }
    printf("\n");
    return 0;
}
// test
int main_test()
{
    // for test Print
    int ans[MAX] = {0}, max = 4;
    ans[0] = 8, ans[1] = 1, ans[2] = 0, ans[3] = -3, ans[4] = -4;
    char name[] = "n";
    Print(ans, max, name);
    return 0;
}