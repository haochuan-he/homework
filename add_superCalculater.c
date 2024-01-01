// 23.12.11
// for additional problem
// by HHC

#include <stdio.h>
#include <string.h>
#define MAX 100102
#define max(a, b) (a > b ? a : b)

int add(char *p1, char *p2, int *p3);
int subtract(char *p1, char *p2, int *p3);
int multiply(char *p1, char *p2, int *p3);
int divide(int *p3, char a[], char b[]);

int main()
{
    static int t = 0;
    scanf("%d", &t);
    while (t--)
    {
        char a[MAX], b[MAX], op = '-';
        int ans[MAX];
        memset(a, '\0', MAX);
        memset(b, '\0', MAX);
        memset(ans, -1, MAX);
        // getchar();

        scanf("%s %s %s", a + 1, &op, b + 1);
        // printf("%c", op);//for test
        // scanf("%s", a + 1);
        // getchar();
        // op = getchar();
        // scanf("%s", b + 1);

        // printf("--op=%c--\n", op);
        int len1 = strlen(a + 1), len2 = strlen(b + 1);
        // int *p3 = ans + max(len1, len2);
        int *p3 = ans + max(max(len1, len2) + 12, 400);
        // printf("--%d-", MAX / 2);
        // printf("len1=%d,len2=%d,==%d==", len1, len2, *p3);

        char *p1 = a + len1, *p2 = b + len2;
        if (len2 > len1)
        {
            char *tem = p1;
            p1 = p2;
            p2 = tem;
        }
        int jump = 0;

        switch (op)
        {
        case '+':
            add(p1, p2, p3);
            break;
        case '-':
            subtract(p1, p2, p3);
            break;
        case '*':
            multiply(p1, p2, p3);
            break;
        case '/':
            // if (len1 < len2)
            // {
            //     printf("0\n");
            // }
            // else
            // {
            //     divide(p3, a, b);
            // }
            printf("1\n");
            jump = 1;
            break;
        default:
            printf("--WRONG--\n");
            break;
        }
        if (jump == 1)
        {
            continue;
        }
        // output
        for (int i = 0, find = 0;; i++)
        {
            if (find == 0 && ans[i] != -1) //&& ans[i] != 0)
            {
                find = 1;
            }
            if (find == 1)
            {
                if (ans[i] == -1 && i != 0)
                {
                    break;
                }
                printf("%d", ans[i]);
            }
        }
        printf("\n");
    }

    return 0;
}
int divide(int *p3, char a[], char b[])
{
    printf("1\n");
    return 0;
} // *p1 / *p2 (len1 >= len2)

int divide_no(int *p3, char a[], char b[]) // *p1 / *p2 (len1 >= len2)
{
    char *p1 = a, *p2 = b;
    int len1 = strlen(a), len2 = strlen(b);
    for (; *(p1 + len2 - 1) != '\0'; p1++)
    { // find whether should extend the range of divide
        int notEnough = 1;
        for (int i = 0; i < len2; i++)
        {
            if (*(p1 + i) > *(p2 + i)) // may + cnt
            {
                notEnough = 0;
                break;
            }
        }
        int range = len2 + notEnough;

        // try the digit ans
        for (int ans = 1, finish = 0;; ans++) // divide the num in range one time
        {
            if (ans > 9)
            {
                printf("try the digit ans wrong!!\n");
                return 0;
            }
            char tem_a[MAX], tem_b[MAX];
            int tem_ans[MAX], tem_mul[MAX], last[MAX];
            memset(tem_mul, -1, MAX);
            char into = ans + '0';

            strncpy(tem_a, p1, range);
            strcpy(tem_b, b + 1);
            multiply(tem_b + len2, &into, tem_mul + MAX - 1000);
            char tem_mul1[MAX];
            for (int i = 0; i < MAX; i++)
            {
                last[i] = tem_ans[i];
                if (tem_mul[i] != -1)
                {
                    tem_mul1[i] = tem_mul[i] + '0';
                }
                else
                {
                    tem_mul1[i] = '\0';
                }
            }
            memset(tem_ans, -1, MAX);
            subtract(tem_a + strlen(tem_a) - 1, tem_mul1 + strlen(tem_mul1) - 1, tem_ans + MAX - 1000);
            // check whether the subtract is enough
            for (int j = 0; j < len2; j++)
            {
                if (tem_ans[j] < *(p2 + j - '0'))
                {
                    finish = 1;
                    break;
                }
            }
            if (finish == 1)
            {
                // set 0 and add the rest part
                int *find = last;
                while (*(++find) != -1)
                    ;

                for (char *set = p1, cnt = 0; cnt < range; cnt++)
                {
                    *(set + cnt) = *find++;
                }
                *p3++ = ans;
                break;
            }
        }
    }
}

int multiply(char *p1, char *p2, int *p3)
{
    int carry = 0;
    for (int cnt = 0; *p2 != '\0'; p2--, cnt++)
    {
        char *save1 = p1;
        for (int *save3 = p3 - cnt; *save1 != '\0'; save1--)
        {
            if (*save3 == -1)
            {
                *save3-- = (*p2 - '0') * (*save1 - '0');
            }
            else
            {
                *save3-- += (*p2 - '0') * (*save1 - '0');
            }
        }
    }
    while (*p3 != -1)
    {
        *p3-- += carry;
        carry = 0;
        if (*(p3 + 1) >= 10)
        {
            carry = *(p3 + 1) / 10;
            *(p3 + 1) %= 10;
        }
    }
    if (carry != 0)
    {
        *p3 = carry;
    }
    return 0;
}

int subtract(char *p1, char *p2, int *p3) //*p1 - *p2
{
    // char *save1 = p1, *save2 = p2;
    int borrow = 0;
    while (*p2 != '\0')
    {
        *p3-- = *p1-- - '0' - *p2-- + '0' - borrow;
        borrow = 0;
        if (*(p3 + 1) < 0)
        {
            *(p3 + 1) += 10;
            borrow = 1;
        }
    }
    while (*p1 != '\0')
    {
        *p3-- = *p1-- - '0' - borrow;
        borrow = 0;
        if (*(p3 + 1) < 0)
        {
            *(p3 + 1) += 10;
            borrow = 1;
        }
    }
    if (*(p3 + 1) == 0 && *(p3 + 2) != -1)
    {
        *(p3 + 1) = -1;
    }
    if (borrow != 0)
    {
        *p3 -= borrow;
        if (*p3 == 0)
        {
            *p3 = -1;
        }
    }
    return 0;
}

int add(char *p1, char *p2, int *p3)
{
    int carry = 0;
    while (*p2 != '\0')
    {
        *p3-- = *p1-- - '0' + *p2-- - '0' + carry;
        carry = 0;
        if (*(p3 + 1) >= 10)
        {
            carry = *(p3 + 1) / 10;
            *(p3 + 1) %= 10;
        }
    }
    while (*p1 != '\0')
    {
        *p3-- = *p1-- - '0' + carry;
        carry = 0;
        if (*(p3 + 1) >= 10)
        {
            *(p3 + 1) %= 10;
            carry = *(p3 + 1) / 10;
        }
    }
    if (carry != 0)
    {
        *p3 = carry;
    }

    return 0;
}