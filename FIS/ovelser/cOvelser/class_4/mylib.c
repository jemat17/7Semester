/* Functions for class 5
Angelo Basteris  22-10-19 
FIS Class @SDU
Ex.11+*/

#include <stdio.h>
#include <math.h>	// Uncomment for compiling from ex13 onwards
#include "mylib.h"



//Uncomment the following block for ex.16
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>

int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
  ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }
  return 0;
}
// Calculates difference in seconds between two timespec objects
double time_diff(struct timespec tstart,struct timespec tend)
{
	double diff;
	diff=((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) - ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec);
	return diff;
}
