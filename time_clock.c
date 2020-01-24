#include <time.h>
#include <stdio.h>



static clock_t clockFrom, clockTo;
static time_t timeFrom, timeTo;

void clockStart(void)
{
    clockFrom = clock();
}

void clockNow(void)
{
    clockTo = clock();
}

double clockDiff(void)
{
    return ((double)(clockTo - clockFrom) / CLOCKS_PER_SEC);
}

void timeStart(void)
{
    timeFrom = time(NULL);
}

void timeNow(void)
{
    timeTo = time(NULL);
}

time_t timeDiff(void)
{
    return timeTo - timeFrom;
}

void wait(void)
{
    int i, j, k;
    for (i = 0; i < 1000; i++){
    for (j = 0; j < 1000; j++){
    for (k = 0; k < 1000; k++){
    }}}
}
int main(void)
{
    printf("time---\n");
    //clockStart();
    timeStart();
    wait();
    timeNow();
    printf("time   = %ld\n", (unsigned long)timeDiff());
    clockStart();
    wait();
    clockNow();
    printf("clock  = %.3f\n", clockDiff());
    return 0;
}