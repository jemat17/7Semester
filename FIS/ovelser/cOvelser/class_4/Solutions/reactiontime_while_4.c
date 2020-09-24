/* C program to measure reaction time - first example
Angelo Basteris - 21-9-2020
FIS Course Syddansk Universitet */
#include<stdio.h>
#include<unistd.h>
#include<time.h>
#include"mylib.h"
#define nreps 5
int main()
{
	//Initial and final time
	struct timespec t_start,t_end;
	// Variable for user input
	char input;
	double reaction_time;
	printf("This software measures your reaction time.\n\nIt will show you a READY message, first - and a GO message after.\nAs you see GO, press a key. Start with your hand on the table\nPress any key when ready\n");
	while(!kbhit())
	{}
	input=getchar();
	while(input!='q')
	{
		printf("Ready\n");
		sleep(2);				// Wait for two seconds
		clock_gettime(CLOCK_MONOTONIC,&t_start);
		printf("Go\n");
		while(!kbhit())
		{}
		input=getchar();			// reads the user input
		clock_gettime(CLOCK_MONOTONIC,&t_end);
		// Shows the reaction time
		reaction_time=((double)t_end.tv_sec + 1.0e-9*t_end.tv_nsec) - ((double)t_start.tv_sec + 1.0e-9*t_start.tv_nsec);
		printf("Your reaction time: %f s\nPress a key to continue or Q to quit\n\n",reaction_time);
		while(!kbhit())
		{}
		input=getchar();
	}
	return 0;
}
