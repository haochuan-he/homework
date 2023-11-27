// 23.11.27
// for practice
// by HHC

#include <stdio.h>

int main()
{
    int input = 0;
    scanf("%x", &input);
    // unsigned int ptr1 = &input;
    float *ptr2 = &input;
    printf("%d\n%u\n%f\n%.4e\n", input, input, *ptr2, *ptr2);

    return 0;
}
// // 23.11.26
// // for homework
// // by HHC

// #include <stdio.h>

// int main()
// {
//     float input1 = -1;
//     scanf("%x", &input1);
//     int *ptr = &input1;
//     printf("%d\n", *ptr);
//     printf("%u\n", *ptr);
//     printf("%.6f\n", input1);
//     printf("%.3e\n", input1);
//     return 0;
// }