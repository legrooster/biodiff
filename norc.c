/* judging the argument of 'c' or 'n' and operating in the given way */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int 
norc(int argc, char **argv)
{
  if (strcmp(argv[1], "-c") == 0)
    return 1;
  else if (strcmp(argv[1], "-n") == 0)
    return -1;
  else
    perror("argv");/* print the reason of the error */
    exit(EXIT_FAILURE);/* shutdown the program */
}
