// 2323.9.22 22点41分
// homework
// by HHC
#include <stdio.h>
int main(void)
{
    int input, rmb50, rmb20, rmb10, rmb5, rmb1;
    scanf("%d", &input);
    rmb50 = input / 50;
    printf("%d\n", rmb50);
    input = input % 50;
    rmb20 = input / 20;
    printf("%d\n", rmb20);
    input = input % 20;
    rmb10 = input / 10;
    printf("%d\n", rmb10);
    input = input % 10;
    rmb5 = input / 5;
    printf("%d\n", rmb5);
    input = input % 5;
    rmb1 = input;
    printf("%d\n", rmb1);

    return 0;
}