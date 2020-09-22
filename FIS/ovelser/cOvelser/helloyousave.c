/* 
 * Store a reply in file program
 * Jeppe Dreyer Matzen
 * FIS 17/09-2020
 * @SDU
 */

#include <stdio.h>

int main()
{
char name[50];
FILE *fptr;
fptr = fopen("output.txt", "w");
printf("%s \n", "What is your name?");

scanf("%49[0-9a-zA-Z ]", name);
fprintf(fptr, "%s\n", name);
fclose(fptr);
printf("%s \n", "Your file is ready now!");
}
