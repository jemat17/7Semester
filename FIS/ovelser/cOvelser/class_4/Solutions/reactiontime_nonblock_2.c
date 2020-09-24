/* C program to measure reaction time - first example
Angelo Basteris - 21-9-2020
FIS Course Syddansk Universitet */
#include<stdio.h>
#include<unistd.h>
#include<time.h>
#include"mylib.h"
int main()
{
	//Initial and final time
	struct timespec t_start,t_end;
	// Variables for user input
	char input;
	int input2;
	double reaction_time;
	printf("This software measures your reaction time.\n\nPress a key when ready.\nAfter that, the software will show you a READY message, first - and a GO message after.\nAs you see GO, press a key. Start with your hand on the table\n");
	while(!kbhit())				// Wait for a keypress
	{}
	input=getchar();
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
	printf("Your reaction time: %f s",reaction_time);
	return 0;
}
