// 24.1.11
// for test
// by HHC
#include <stdio.h>
int main()
{
    int a = 1, b = 0;

    // step by step
    b += ++a;
    printf("%d %d\n", a, b);
    b += ++a;
    printf("%d %d\n", a, b);
    b += ++a;
    printf("%d %d\n", a, b);
    // original version
    a = 1;
    b = 0;
    b = (++a) + (++a) + (++a);
    printf("%d %d\n", a, b);

    return 0;
}

// #include <stdio.h>
// #include <stdlib.h>

// void swap(int &a, int &b);

// int main()
// {
//     int a = 12, b = 0;
//     printf("a=%d b=%d\n", a, b);
//     swap(a, b);
//     printf("a=%d b=%d\n", a, b);
// }

// void swap(int &a, int &b){

// }
