/* compare in mode "-c" */

#define MAX_LINE_LENGTH  1024  /* the longest length of the buffer */
#define MAX_LINE         20    /* the maximum of the column */
#define MAXWORD          100   /* the maximum length of each column*/

int ctype(char **word1, char **word2, int *column1, int *column2);

void
ccmp(FILE *fp1, FILE *fp2,
  FILE *AB, FILE *BA, FILE *A_B,
  int *column1, int *column2)
{
/* create the buffer for each line */
	char buffer1[MAX_LINE_LENGTH];
	char buffer2[MAX_LINE_LENGTH];
/* create the array to store each column in the same line */
	char *word1[MAX_LINE];
	char *word2[MAX_LINE];
/* allocate the memory for the array */
	int i; /* make a counter */
	for ( i = 0; i < MAX_LINE; i++)
		word1[i] = (char *)alloc(MAXWORD*sizeof(char *));
	for ( i = 0; i < MAX_LINE; i++)
                word2[i] = (char *)alloc(MAXWORD*sizeof(char *));


	char *temp; /* act as the buffer for split */
	char *whitespace = " \t\n\v\f\b"; /* token */
	int state = 0; /* ensure whether the line has been put out */

/* read the file into the buffer */
	while ((fgets(buffer1, MAX_LINE_LENGTH, fp1)) != NULL){
		temp = strdup(buffer1);
/* strtok will alter the buffer so a temp is needed*/
		for (i = 0, word1[i] = strtok(temp, whitespace);
		  word1[i] != NULL;
		  word1[i] = strtok(NULL, whitespace))
/* the for loop is used to split the line into columns */
			i++;
/* these two loops resemble the former loops */
		fseek(fp2, (long)0, SEEK_SET); 
		while ((fgets(buffer2, MAX_LINE_LENGTH, fp2)) != NULL){
			temp = strdup(buffer2);
			for (i = 0, word2[i] = strtok(temp, whitespace);
			  word2[i] != NULL;
			  word2[i] = strtok(NULL, whitespace))
				i++;
/* if the coordinates have intersection, the return will be 1 */
			if ( ctype(word1, word2, column1, column2) > 0){
				fputs(buffer1, AB); /* output the line */
				fputs(buffer2, BA);
				state = 1; /* alter the state */
				continue; 
			}				
		}
		if (state == 0)
			fputs( buffer1, A_B );
		state = 0; /* initialize the state */
	}
/*        for ( i = 0; i < MAX_LINE; i++)
                free(word1[i]);
        for ( i = 0; i < MAX_LINE; i++)
                free(word2[i]);
*/
}

