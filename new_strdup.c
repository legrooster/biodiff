#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char *strdup(char const *src)
{
	char *line;
	line = (char *)malloc(strlen(src) + 1);
	if(line != NULL)
		strcpy(line, src);
	return line;
}
