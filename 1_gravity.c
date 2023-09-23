// 2023.9.23 10点01分
// homework
// by HHC
#include <stdio.h>

int main(void)
{
    const double G = 6.674e-11, M = 77.15;
    double m, R; // force=(G*M*m)/(R*R)
    scanf("%lf %lf", &m, &R);
    printf("%.3e", (G * M * m) / (R * R));

    return 0;
}