#include <stdio.h>
#include <float.h>

int main(void)
{
    float e_f = 1.0f, tmp_f;
    double e_d = 1.0, tmp_d;

    while (1)
    {
        tmp_f = e_f / 2.0f;
        if (1.0f + tmp_f == 1.0f)
        {
            break;
        }
        e_f = tmp_f;
    }

    while (1)
    {
        tmp_d = e_d / 2.0;
        if (1.0 + tmp_d == 1.0)
        {
            break;
        }
        e_d = tmp_d;
    }

    printf("epsilon(float)\t:\t%30.25f\n", e_f);
    printf("FLT_EPSILON\t:\t%30.25f\n", FLT_EPSILON);
    printf("epsilon(double)\t:\t%30.25lf\n", e_d);
    printf("FLT_EPSILON\t:\t%30.25lf\n", DBL_EPSILON);

    return 0;
}