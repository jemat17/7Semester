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
char name[50];
time_t klokken;
FILE *fptr;

fptr = fopen("output.txt", "r");
//printf("%s \n", "What is your name?");

//scanf("%49[0-9a-zA-Z ]", name);

fscanf(fptr, "%49[0-9a-zA-Z ]", name);
fclose(fptr);

time(&klokken);
printf("The time is %ld \n", klokken);
}
