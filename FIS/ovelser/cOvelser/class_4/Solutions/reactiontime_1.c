/* C program to measure reaction time - first example
Angelo Basteris - 21-9-2020
FIS Course Syddansk Universitet */
#include<stdio.h>
#include<unistd.h>
#include<time.h>
int main()
{
	//Initial and final time
	struct timespec t_start,t_end;
	// Variables for user input
	int input1,input2;
	double reaction_time;
	printf("Press C and enter when ready\n");
	scanf("%d", &input1);
	getchar();				// We need getchar() after a scanf otherwise the following scanf will be immediate
	printf("Ready\n");
	sleep(2);				// Wait for two seconds
	clock_gettime(CLOCK_MONOTONIC,&t_start);
	printf("Go\n");
	scanf("%d",&input2);			// Waits for user input
	clock_gettime(CLOCK_MONOTONIC,&t_end);
	// Shows the reaction time
	reaction_time=((double)t_end.tv_sec + 1.0e-9*t_end.tv_nsec) - ((double)t_start.tv_sec + 1.0e-9*t_start.tv_nsec);
	printf("Your reaction time: %f s",reaction_time);
	return 0;
}
