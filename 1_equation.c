// 2023.9.23 10点26分
// homework
// by HHC
#include <stdio.h>
#include <math.h>

/*int main(void)
{
    double x1, p, q;
    scanf("%lf %lf", &p, &q);
    // 验证开三次方之方法
    // double input;
    // scanf("%lf", &input);
    // printf("%f", pow(input, 1.0 / 3));
    double part1, part2;
    part1 = -q / 2.0;
    part2 = pow((q * q / 4 + p * p * p / 27), 1.0 / 2);
    printf("%lf %lf", part1, part2); 
    x1 = pow(part1 + part2, 1.0 / 3) + pow(part1 - part2, 1.0 / 3);
    printf("%.3f", x1);
    return 0;
}*/

int main(void)
{
    double x1, p, q;
    scanf("%lf %lf", &p, &q);
    // 验证开三次方之方法
    // double input;
    // scanf("%lf", &input);
    // printf("%f", pow(input, 1.0 / 3));
    double part1, part2;
    part1 = -q / 2.0;
    part2 = sqrt((q * q / 4.0) + (p * p * p / 27.0));
    // printf("%lf %lf", part1, part2);
    x1 = cbrt((part1 + part2)) + cbrt((part1 - part2));
    printf("%.3f", x1);
    return 0;
}