#include <stdio.h>
#include <math.h>

double G_sin(double theta);
double G_cos(double theta);

int main()
{
    printf("G_sin = %.20f\n", G_sin(M_PI / 4));
    printf("sin   = %.20f\n", sin(M_PI / 4));

    printf("G_cos = %.20f\n", G_cos(M_PI / 4));
    printf("cos   = %.20f\n", cos(M_PI / 4));

        
    return 0;
}

double G_sin(double theta)
{
    int i, cnt = 1;
    double b_ans = 0, ans = 0, b_num;

    while (1)
    {
        if(cnt == 1)
        {
            b_num = theta;
        }
        else
        {
            b_num * -1 * theta * theta; //*-theta^2
            b_num = (b_num * -1 * theta * theta)/(cnt * (cnt - 1));
        }
        cnt += 2;
        //計算
        ans += b_num;

        if (ans == b_ans)
        {
            break;
        }
        b_ans = ans;
    }
    return ans;
}

double G_cos(double theta)
{
    int i, cnt = 0;
    double b_ans = 0, ans = 0, b_num;

    while (1)
    {
        if(cnt == 0)
        {
            b_num = 1;
        }
        else
        {
            b_num * -1 * theta * theta; //*-theta^2
            b_num = (b_num * -1 * theta * theta)/(cnt * (cnt - 1));
        }
        cnt += 2;
        //計算
        ans += b_num;
        if (ans == b_ans)
        {
            break;
        }
        b_ans = ans;
    }
    return ans;
}