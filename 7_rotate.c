// 23.11.18
// for homework
// by HHC

#include <stdio.h>
#include <stdlib.h>
int a, b, c;
int position[2][3];

int rotate(void);
int the_rest(void);
int exchange(void);

int main()
{
    scanf("%d%d%d", &a, &b, &c);
    getchar();
    position[0][2] = a;
    position[1][2] = b;
    // position[0][0] = position[2][0] - position[1][0];
    // position[0][1] = position[2][1] - position[1][1];
    rotate();
    printf("%d %d %d %d", position[0][1], position[0][2], position[1][1], position[1][2]);
    return 0;
}

int rotate(void)
{
    char ch = getchar();
    if (ch == EOF) // EOF on OJ
    {
        return 0;
    }

    switch (ch)
    {
    case 'W':
        position[0][2] = position[0][1] - the_rest();
        break;
    case 'A':
        position[1][2] = position[1][1] - the_rest();
        break;
    case 'S':
        position[0][1] = position[0][2] + the_rest();
        break;
    case 'D':
        position[1][1] = position[1][2] + the_rest();
        break;
    }

    exchange();
    return rotate();
}
int the_rest(void)
{
    return a + b + c - abs(position[0][1] - position[0][2]) - abs(position[1][1] - position[1][2]);
}
int exchange(void)
{
    if (position[0][2] < position[0][1])
    {
        int temp = position[0][2];
        position[0][2] = position[0][1];
        position[0][1] = temp;
    }
    if (position[1][2] < position[1][1])
    {
        int temp = position[1][2];
        position[1][2] = position[1][1];
        position[1][1] = temp;
    }
    return 0;
}