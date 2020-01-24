#include <stdio.h>
#include <math.h>

double G_log(double a);

int main()
{
    double a = 123;
    printf("G_log = %f\n", G_log(a));
    printf("log   = %f\n", log(a));    
    
    return 0;
}

double G_log(double a)
{
    int i, k = 0;
    double b_ans = 0, ans = 0, num1 = 1, num2 = 1;

    while (1)
    {
        for (i = 0; i < 2*k+1; i++) {
            num1 *= a - 1;
            num2 *= a + 1;
        }
        ans += (2 * num1) / ((2 * k + 1)*num2);
        k++;

        if (b_ans == ans)
            break;
        b_ans = ans;
        /* if (k > 1000)
        {
            break;
        } */
        
    }
    return ans;
}