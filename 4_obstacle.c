// 23.10.22
// homework
// by HHC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int xa, ya, xb, yb, xc, yc, lmin = 0;
char u = 'U', d = 'D', l = 'L', r = 'R';

// int abv(int a, int b);
int max(int a, int b);
int min(int a, int b);
int isob(void);
int go(char a, int step);

// for really rectangel circumstance
int horizonal(void);
int vertical(void);

int main()
{
    scanf("%d%d%d%d%d%d", &xa, &ya, &xb, &yb, &xc, &yc);

    // for part 1: rectangel
    // TESTED
    if (abs(xa - xb) > 0 && abs(ya - yb) > 0)
    {
        lmin = abs(xa - xb) + abs(ya - yb);
        printf("%d\n", lmin);

        if (isob())
        {
            if (xb == xc || ya == yc)
            { // vertical first
                vertical();
                // horizonal second
                horizonal();
            }
            else if (xa == xc || yb == yc)
            {
                horizonal();
                vertical();
            }
            else
            {
                horizonal();
                vertical();
            }
        }
        else //(isob() == 0) || isob()==1&&(is not really on the line of rectangle)
        {    // horizonal
            horizonal();
            // vertical
            vertical();
        }
    }

    // part 2
    if (xa == xb)
    {
        if (isob() == 0)
        {
            lmin = abs(ya - yb);
            printf("%d\n", lmin);
            vertical();
        }
        else // isob()==1
        {
            lmin = abs(ya - yb) + 2;
            printf("%d\n", lmin);
            if (ya > yb)
            {
                go(d, abs(ya - yc) - 1);
                printf("RDDL");
                go(d, abs(yc - yb) - 1);
            }
            else
            {
                go(u, abs(ya - yc) - 1);
                printf("RUUL");
                go(u, abs(yc - yb) - 1);
            }
        }
    }

    // part 3
    if (ya == yb)
    {
        if (isob() == 0)
        {
            lmin = abs(xa - xb);
            printf("%d\n", lmin);
            horizonal();
        }
        else // isob()==1
        {
            lmin = abs(xa - xb) + 2;
            printf("%d\n", lmin);
            if (xa < xb)
            {
                go(r, abs(xa - xc) - 1);
                printf("URRD");
                go(r, abs(xb - xc) - 1);
            }
            else
            {
                go(l, abs(xa - xc) - 1);
                printf("ULLD");
                go(l, abs(xb - xc) - 1);
            }
        }
    }
    return 0;
}

// // test
// go(u, 5);
// go(l, 12);
// printf("???%d", isob());

/**************************************************************
 * abv:absolute value of (a-b)
 *
 * TESTED
 */
// int abs(int a, int b)
// {
//     if (a - b > 0)
//     {
//         return (a - b);
//     }
//     else
//     {
//         return (b - a);
//     }
// }
/***************************************************************
 *  max:return the bigger one of a,b
 *
 * TESTED
 */
int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}
/****************************************************************
 * min:return the samller one of a,b
 *
 * TESTED
 */
int min(int a, int b)
{
    if (a > b)
    {
        return b;
    }
    else
    {
        return a;
    }
}
/*****************************************************************************
 * isob:(is obstacal)to judge whether the obstacle is in the rectangle of A_B;
 *      return 1 if turn; return 0 if flase
 *
 * TESTED
 */
int isob(void)
{
    if ((xc < min(xa, xb) || xc > max(xa, xb)) || (yc < min(ya, yb) || yc > max(ya, yb)))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
/**********************************************************************
 *  go: printf char a for 'step' times;
 *
 *TESTED
 */
int go(char a, int step)
{
    if (step > 10000)
    {
        char buffer[10000];
        memset(buffer, a, 10000);
        for (int j = 0; j < (step / 10000); j++)
        {
            printf("%s", buffer);
        }
    }
    for (int i = 0; i < (step % 10000); i++)
    {
        putchar(a);
    }
    // for (int i = 0; i < step; i++)
    // {
    //     putchar(a);
    // }
    // return 0;
}
/************************************************************************
 * horizonal: go horizonally form A to B
 *
 * TESTED
 */
int horizonal(void)
{
    if (xa < xb)
    {
        go(r, abs(xa - xb));
    }
    else
    {
        go(l, abs(xa - xb));
    }
    return 0;
}
/***************************************************************************
 *vertical: go vertically form A to B
 *
 * TESTED
 */
int vertical(void)
{
    if (ya < yb)
    {
        go(u, abs(ya - yb));
    }
    else
    {
        go(d, abs(ya - yb));
    }
    return 0;
}