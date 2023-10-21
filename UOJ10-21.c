// 23.10.21
//  for UOJ homework
// by HHC

#include <stdio.h>

int trans(int state, int i, int n, int t, int out);

int main()
{
    int state, i, n, t, out;
    scanf("%d%d%d%d%d", &state, &i, &n, &t, &out);
    printf("%d", trans(state, i, n, t, out));
    return 0;
}

int trans(int state, int i, int n, int t, int out)
{
    switch (state)
    {
    case 0:
        if (out == i)
        {
            state = 1;
        }
        break;
    case 1:
        if (out == n)
        {
            state = 2;
        }
        else if (out == i)
        {
            ;
        }
        else
        {
            state = 0;
        }
        break;
    case 2:
        if (out == t)
        {
            state = 3;
        }
        else if (out == i)
        {
            state = 1;
        }
        else
        {
            state = 0;
        }
        break;
    case 3:
        if (out == i)
        {
            state = 1;
        }
        else
        {
            state = 0;
        }
        break;
    }
    return state;
}