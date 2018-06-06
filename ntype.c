/* compare the two genes in the "-n" mode */

int 
ntype(char **word1, char **word2, int *column1, int *column2)
{
	if ( strstr( word1[column1[0]], word2[column2[0]]) == NULL 
	  && strstr( word2[column2[0]], word1[column1[0]]) == NULL )
		return 0;
	else
		return 1;
}
