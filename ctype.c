/* compare the coordinate in "-c" mode */

int 
ctype(char **word1, char **word2, int *column1, int *column2)
{
	int upA, upB, downA, downB;
/* ensure the coordinates of the two genes */
	if ( atoi(word1[column1[0]]) > atoi(word1[column1[1]]) ){
		upA = atoi( word1[column1[0]] );
		downA = atoi( word1[column1[1]] );
	}else{
		upA = atoi( word1[column1[1]] );
		downA = atoi( word1[column1[0]] );
	}

	if ( atoi(word2[column2[0]]) > atoi(word2[column2[1]]) ){
                upB = atoi( word2[column2[0]] );
                downB = atoi( word2[column2[1]] );
        }else{
                upB = atoi( word2[column2[1]] );
                downB = atoi( word2[column2[0]] );
        }
/*printf("%d\t%d\t%d\t%d\n",upA,downA,upB,downB);*/
/* decide whether the two genes have intersection */
	if (upA < downB || upB < downA) /* have no intersection */
		return 0;
	else
		return 1;
}
