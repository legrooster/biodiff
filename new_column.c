/* comfirm the exactly needed column of the data */
#include"strdup.c"

char *strdup(char const *src);


void
column(int argc, char *argv[], int num, int *column_num)
{
/* the arguments should be enough and the corresponding column should contain reasonable argument */
        if (argc != 8){
                perror("lack of argument: please input the arguments according to the instruction ");
                exit(EXIT_FAILURE);
        }
                
        if ((strcmp(argv[2], "-a") != 0) || (strcmp(argv[4], "-b") != 0)){
                perror("argument: the option should be \"-a\" and \"-b\" before the column number");
                exit(EXIT_FAILURE);
        } 
	
	int j = 0;  /* counter */
	char *total;  
/* get all of the column that need to be recorded as data */

	char *temp_num = (char *)malloc(strlen(argv[num]));  
/* split the numbers in the pointer "total" */
  
	total = strdup(argv[num]);

/* split the number into the given array */
	for(temp_num = strtok(total, ",");
	  temp_num != NULL; 
	  temp_num = strtok(NULL, ",")){
		column_num[j++] = atoi(temp_num) ;
	}
	
	free(temp_num);
	return;
}

