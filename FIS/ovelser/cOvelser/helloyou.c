/* Hallo world program
Jeppe Dreyer Matzen
Øvelse 1
FIS 

*/
#include <stdio.h>

int  main()
{
char name[50];
printf( "What is your name?\n");
//scanf("%s", name);
scanf("%49[0-9a-zA-Z ]", name);
printf("Hallo %s \n", name);

return 0;
}
