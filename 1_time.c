// 2023.9.23 00点02分
// homework
// by HHC

#include <stdio.h>

int main(void)
{
    int day, year, hour, minute, second;
    char month[15], weekday[15];
    scanf("%s %d %d %s %d %d %d", &month, &day, &year,
          &weekday, &hour, &minute, &second);
    printf("%.3s %.3s %.2d %.2d:%.2d:%.2d %.4d", weekday, month,
           day, hour, minute, second, year);

    return 0;
}