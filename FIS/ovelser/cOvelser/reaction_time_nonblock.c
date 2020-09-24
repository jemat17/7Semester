/* 
 * Reaction time in c
 * This program will time your reaction time from GO! to you press a key
 * Jeppe Dreyer Matzen
 * FIS 17/09-2020
 * @SDU
 */

#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main()
{
char input, input2;
struct timespec t_start={0,0};
struct timespec t_end={0,0};

priintf("Check your reaction time ");
printf("\n Press a key when ready ");
//scanf(" %c", input);

printf("\n Ready");
sleep(1);
printf("\n Set");
sleep(2);
printf("\n GO!");
getchar();
clock_gettime(CLOCK_MONOTONIC,&t_start);

//scanf(" %c", input2);

clock_gettime(CLOCK_MONOTONIC,&t_end);

printf("Your reaction time was: %.3f seconds\n",((double)t_end.tv_sec + 1.0e-9*t_end.tv_nsec) - ((double)t_start.tv_sec + 1.0e-9*t_start.tv_nsec));

}
