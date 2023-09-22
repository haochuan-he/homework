// 2023.9.22
// homework
// by HHC
#include <stdio.h>

int main(void)
{
    int input;
    char first, second;
    scanf("%d", &input);
    // first = input;
    // printf("%d %c\n", input, first);
    printf("%d %c\n", input, input);
    second = input - 'A' + 'a';
    printf("%d %c", second, second);

    return 0;
}
