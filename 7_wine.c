// 23.11.17
// for homework
// by HHC

#include <stdio.h>

int wine[10012][2];

int pay(int price, int rest, int total);

int main()
{
    int n = 0, l = 0;
    scanf("%d%d", &n, &l);

    for (int i = 1; i <= n; i++) // price
    {
        scanf("%d", &wine[i][0]);
    }
    for (int i = 1; i <= n; i++) // ml
    {
        scanf("%d", &wine[i][1]);
    }

    int price = pay(0, l, n);
    printf("%d", price);

    return 0;
}

int pay(int price, int rest, int total)
{
    if (rest == 0)
    {
        return price;
    }

    int max = 0, max_index = 1;
    for (int i = 1; i <= total; i++)
    {
        if (wine[i][0] > max)
        {
            max = wine[i][0];
            max_index = i;
        }
    }
    if (rest >= wine[max_index][1])
    {
        rest = rest - wine[max_index][1];
        price += wine[max_index][1] * wine[max_index][0];
        wine[max_index][0] = 0;
    }
    else
    {
        price += rest * wine[max_index][0];
        rest = 0;
    }
    return pay(price, rest, total);
}