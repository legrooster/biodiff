/* get the last file in the "-n" mode */

void 
rencmp(FILE *fp2, FILE *fp3, FILE *B_A, int *column2)
{
/* create the buffer for each line */
        char buffer2[MAX_LINE_LENGTH];
        char buffer3[MAX_LINE_LENGTH];
/* create the array to store each column in the same line */
        char *word2[MAX_LINE];
        char *word3[MAX_LINE];
/* allocate the memory for the array */
        int i; /* make a counter */
        for ( i = 0; i < MAX_LINE; i++)
                word2[i] = (char *)alloc(MAXWORD*sizeof(char *));
        for ( i = 0; i < MAX_LINE; i++)
                word3[i] = (char *)alloc(MAXWORD*sizeof(char *));


        char *temp; /* act as the buffer for split */
        char *whitespace = " \t\n\v\f\b"; /* token */
        int state = 0; /* ensure whether the line has been put out */

/* read the file into the buffer */
	fseek(fp2, (long)0, SEEK_SET);
        while ((fgets(buffer2, MAX_LINE_LENGTH, fp2)) != NULL){
                temp = strdup(buffer2);
/* strtok will alter the buffer so a temp is needed*/
                for (i = 0, word2[i] = strtok(temp, whitespace);
                  word2[i] != NULL;
                  word2[i] = strtok(NULL, whitespace))
/* the for loop is used to split the line into columns */
                        i++;
		fseek(fp3, (long)0, SEEK_SET);
/* these two loops resemble the former loops */
                while ((fgets(buffer3, MAX_LINE_LENGTH, fp3)) != NULL){
                        temp = strdup(buffer3);
                        for (i = 0, word3[i] = strtok(temp, whitespace);
                          word3[i] != NULL;
                          word3[i] = strtok(NULL, whitespace))
                                i++;
/* if the coordinates have intersection the return will be 1 */
                        if ( ntype(word2, word3, column2, column2) > 0){
                                state = 1; /* alter the state */
                                break;
                        }
                }
                if (state == 0)
                        fputs( buffer2, B_A );
                state = 0; /* initialize the state */
        }
/*        for ( i = 0; i < MAX_LINE; i++)
		free(word2[i]);
        for ( i = 0; i < MAX_LINE; i++)
		free(word3[i]);
*/
}
