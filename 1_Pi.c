// 2023.9.22 23点05分
// homework
// by HHC
#include <stdio.h>
#include <math.h>

int main(void)
{ // the next lines is to learn how to use function
    // printf("%f", log(2));//log = ln
    // printf("%f", 4 * atan(1));//atan output the num with pi
    double pi1, pi2;
    const double M = 640320, N = 774, W = 163;
    pi1 = log(M * M * M + N) / (sqrt(W));
    printf("%.15lf\n", pi1);
    const double V = 1.0 / 5, U = 1.0 / 239;
    pi2 = 16 * atan(V) - 4 * atan(U);
    printf("%.15lf", pi2);

    return 0;
}