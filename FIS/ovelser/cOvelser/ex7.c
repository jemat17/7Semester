/* 
 * Store a reply in file program
 * Jeppe Dreyer Matzen
 * FIS 17/09-2020
 * @SDU
 */

#include <stdio.h>
#include <time.h>

int main()
{

time_t klokken;
FILE *fptr;

struct timespec t_start={0,0};
struct timespec t_end={0,0};
for(int i = 0; i < 1000000; i++){

clock_gettime(CLOCK_MONOTONIC,&t_start);
printf("Hello World!");
clock_gettime(CLOCK_MONOTONIC,&t_end);
printf("Printing hello world took about %.9f seconds\n",((double)t_end.tv_sec + 1.0e-9*t_end.tv_nsec) - ((double)t_start.tv_sec + 1.0e-9*t_start.tv_nsec));
}

}
