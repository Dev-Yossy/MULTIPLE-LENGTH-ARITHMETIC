#include <stdio.h>
#include <math.h>

int main(void)
{
    double a = 1.23456;
    double b = 1.23442;
    double c;

    c = a - b;

    printf("a = %13.10f\n", a);
    printf("b = %13.10f\n", b);
    printf("c = %13.10f\n", c);

    double h = 1.234567;
    double x = 8.76543;
    double y = 5.8765234;

    double L23 = 1.0 - cos(h);
    double R23 = 2.0 * sin(h / 2.0) * sin(h / 2.0);

    double L24 = sin(x + h) - sin(x);
    double R24 = 2.0 * cos(x + h / 2.0) * sin(h / 2.0);

    double L25 = cos(x) * cos(x) - sin(x) * sin(x);
    double R25 = cos(2.0 * x);

    double L26 = log(x) - log(y);
    double R26 = log(x / y);

    printf("L23 : %13.20lf\n", L23);
    printf("R23 : %13.20lf\n", R23);
    printf("L24 : %13.20lf\n", L24);
    printf("R24 : %13.20lf\n", R24);
    printf("L25 : %13.20lf\n", L25);
    printf("R25 : %13.20lf\n", R25);
    printf("L26 : %13.20lf\n", L26);
    printf("R26 : %13.20lf\n", R26);
    

    return 0;
}