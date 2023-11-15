// 23.11.13
// for homework
// by HHC

#include <stdio.h>
#include <math.h>
#define P 0.0001
#define MAX 25

double Fx(double x);
double Simpson(double a, double b);
double ASM(double l, double r, double precision); // Adaptive Simpson's Method
int a[MAX], n, p;

int main()
{
    scanf("%d%d", &n, &p);
    for (int i = 0; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    double a = 0.0, b = 0.0;
    scanf("%lf%lf", &a, &b);

    printf("%lf", ASM(a, b, P));

    return 0;
}

double ASM(double l, double r, double precision)
{
    double mid = (l + r) / 2;
    double S = Simpson(l, r);
    double SL = Simpson(l, mid);
    double SR = Simpson(mid, r);
    // printf("%lf", SL + SR + (SL + SR - S) / 15);
    if (fabs(SL + SR - S) < precision)
    {
        return SL + SR + (SL + SR - S) / 15;
    }

    return ASM(l, mid, precision / 2) + ASM(r, mid, precision / 2);
}

double Simpson(double a, double b)
{
    return (4.0 * Fx((a + b) / 2) + Fx(a) + Fx(b)) * fabs(b - a) / 6;
}

double Fx(double x)
{
    double fx = 0.0;
    for (int i = 0; i <= n; i++)
    {
        fx += pow(x, i) * a[i];
    }
    // printf("__%lf__", pow(fx, p));
    return pow(fx, p);
}
