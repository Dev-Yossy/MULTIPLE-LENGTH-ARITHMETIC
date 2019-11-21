#include <stdio.h>
#include <math.h>

#define CHOOSE(a) CHOOSE2 a
#define CHOOSE2(a0,a1,a2,a3,a4,x,...) x

#define fmax_N(...) CHOOSE((__VA_ARGS__,fmax_5,fmax_4,fmax_3,fmax,fmax_1,~))(__VA_ARGS__)

double fmax_1(double a0) {
    return a0;
}

double fmax_3(double a0, double a1, double a2) {
    return fmax(fmax(a0, a1), a2);
}

double fmax_4(double a0, double a1, double a2, double a3) {
    return fmax_3(fmax(a0, a1), a2, a3);
}

double fmax_5(double a0, double a1, double a2, double a3, double a4) {
    return fmax_4(fmax(a0, a1), a2, a3, a4);
}

int main(int argc, char *argv[]) {
    printf("%g\n", fmax_N(1.0)); // --> fmax_1(1.0)
    printf("%g\n", fmax_N(1.0, 3.0)); // --> fmax(1.0, 3.0)
    printf("%g\n", fmax_N(1.0, 3.0, -2.4)); // --> fmax_3(1.0, 3.0, -2.4)
    printf("%g\n", fmax_N(1.0, 3.0, -2.4, 0.34)); // --> fmax_4(1.0, 3.0, -2.4, 0.34)
    printf("%g\n", fmax_N(1.0, 3.0, -2.4, 0.34, 9.32)); // --> fmax_5(1.0, 3.0, -2.4, 0.34, 9.32)
}