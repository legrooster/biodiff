#include"alloc.c"
#include"tree.c"

#define MAXWORD 1024
#define MAXLINE 20

int ctype(int downA, int upA, int downB, int upB);
void swap( int *a, int *b );


/* count the rows of the file */
int count_row( FILE *fp ){
	int i = 0;
	char *buffer = (char *)alloc( sizeof(char *)*MAXWORD );
	for( fseek( fp, (long)0, SEEK_SET ); fgets( buffer, MAXWORD, fp ) != NULL; i++ ){	
	}
	return i;
}

/* read the exact column in an array */
char **getname( FILE *fp, int column_num, char **column){
	int i, j;
	int row = count_row( fp );
	char const *whitespace = " #;\t\b\f\n\v\"\'";
	char *buffer = (char *)alloc( sizeof(char * )*MAXWORD );
	char **word = (char **)alloc( sizeof(char *)*MAXLINE );
	for( fseek( fp, (long)0, SEEK_SET ), i = 0; fgets( buffer, MAXWORD, fp ) != NULL; i++){
		for( j = 0, word[j] = strtok(buffer, whitespace); 
		 word[j] != NULL; word[j] = strtok(NULL, whitespace) ) 
			j++;	
		column[i] = strdup( word[column_num] );
	}
/*	free(buffer);
*/	free(*word);
	return column;
}

/* read the coordinate in pair of arrays */
int *getcoor( FILE *fp, int column_num, int *column){
        int i, j;
        int row = count_row( fp );
        char const *whitespace = " \t\b\f\n\v\'\"";
        char *buffer = (char *)alloc( sizeof(char * )*MAXWORD );
        char **word = (char **)alloc( sizeof(char *)*MAXLINE );
        for( fseek( fp, (long)0, SEEK_SET ), i = 0; fgets( buffer, MAXWORD, fp ) != NULL; i++){
		
		for( j = 0, word[j] = strtok(buffer, whitespace);
		 word[j] != NULL; 
		 word[j] =  strtok(NULL, whitespace) ){
                        j++;
		}
                column[i] = atoi( word[column_num] );
        }

/*	free(buffer);
*/	free(*word);
        return column;
}

/* quickly sort an array in or from small to big */
void quicksort( int *array, int *according, int begin, int end ){
	int i, j;
	if ( begin < end){
		i = begin + 1;
		j = end;
		while(i < j){
			if( array[i] > array[begin] ){
				swap( &array[i], &array[j] );
				swap( &according[i], &according[j] );
				j--;
			}else{
				i++;
			}
		}
		
		if( array[i] >= array[begin] )
			i--;
		
		swap( &array[begin], &array[i] );
		swap( &according[begin], &according[i] );
		quicksort(array, according, begin, i);
		quicksort(array, according, j, end);
	}
	
}

/* swap the the two numbers */
void swap( int *a, int *b ){
	int temp;

	temp = *b;
	*b = *a;
	*a = temp;
}

/* compare the file in option '-c' */
void ccmp( FILE *fp1, FILE *fp2, FILE *AB, FILE *BA, FILE *A_B, FILE *B_A, int *column1, int *column2 ){
        int rowA = count_row( fp1 );
        int rowB = count_row( fp2 );

	int *coorA1 = (int *)alloc(sizeof(int *)*(rowA+1));
	int *coorA2 = (int *)alloc(sizeof(int *)*(rowA+1));
	int *coorB1 = (int *)alloc(sizeof(int *)*(rowB+1));
	int *coorB2 = (int *)alloc(sizeof(int *)*(rowB+1));
	coorA1 = getcoor( fp1, column1[0], coorA1 );
	coorA2 = getcoor( fp1, column1[1], coorA2 );
	coorB1 = getcoor( fp2, column2[0], coorB1 );
	coorB2 = getcoor( fp2, column2[1], coorB2 );

	int *stateA = (int *)alloc(sizeof(int *)*(rowA+1));
	int *stateB = (int *)alloc(sizeof(int *)*(rowB+1));

	int i; /* counter */
/*	int state = 0;
*/	for (i = 0; i < rowA; i++)
		stateA[i] = 0;
	for (i = 0; i < rowB; i++)
		stateB[i] = 0;

	int a = 0, b = rowB - 1;
	quicksort( coorB1, coorB2, a, b );
/* bisection method 1 */
	int c;
	char *buffer = (char *)alloc( sizeof(char * )*MAXWORD ); 
	for( i = 0, fseek( fp1, (long)0, SEEK_SET ); fgets( buffer, MAXWORD, fp1) != NULL; i++ ){
/*		state = 0;
*/	
		a = 0;
		b = rowB - 1;
		c = (a + b)/2 + 1;
		if (ctype( coorA1[i], coorA2[i], coorB1[a], coorB2[a]) == 0 
		  || ctype( coorA1[i], coorA2[i], coorB1[b], coorB2[b]) == 0 ){
			stateA[i] = 1;
		}
		while( a + 1 < b ){
			if( ctype( coorA1[i], coorA2[i], coorB1[c], coorB2[c]) > 0){
				a = c;
				c = (a + b)/2;
			}else if (ctype( coorA1[i], coorA2[i], coorB1[c], coorB2[c]) < 0){
				b = c;
				c = (a + b)/2; 
			}else{
				stateA[i] = 1; 
				break;
			}
		};
/*		if (state==0)
			fputs( buffer, A_B );
		else
			fputs( buffer, AB );
*/	}
/**/
        coorB1 = getcoor( fp2, column2[0], coorB1 );
        coorB2 = getcoor( fp2, column2[1], coorB2 );

        a = 0, b = rowB - 1;
        quicksort( coorB2, coorB1, a, b );

        for( i = 0, fseek( fp1, (long)0, SEEK_SET ); fgets( buffer, MAXWORD, fp1) != NULL; i++ ){
                a = 0;
                b = rowB - 1;
                c = (a + b)/2 + 1;
                if (ctype( coorA1[i], coorA2[i], coorB1[a], coorB2[a]) == 0 
                  || ctype( coorA1[i], coorA2[i], coorB1[b], coorB2[b]) == 0 ){
                        stateA[i] = 1;

                }
              while( a + 1 < b ){
                        if( ctype( coorA1[i], coorA2[i], coorB1[c], coorB2[c]) > 0){
                                a = c;
                                c = (a + b)/2;
                        }else if (ctype( coorA1[i], coorA2[i], coorB1[c], coorB2[c]) < 0){
                                b = c;
                                c = (a + b)/2;
                        }else{
                                stateA[i] = 1;
                                break;
                        }
                }
                if (stateA[i]==0)
                        fputs( buffer, A_B );
                else
                        fputs( buffer, AB );
        }

/**/
        coorB1 = getcoor( fp2, column2[0], coorB1 );
        coorB2 = getcoor( fp2, column2[1], coorB2 );

	a = 0, b = rowA - 1;
        quicksort( coorA1, coorA2, a, b );
/* bisection method 3 */
	for( i = 0, fseek( fp2, (long)0, SEEK_SET ); fgets( buffer, MAXWORD, fp2) != NULL; i++ ){
/*		state = 0;
*/		a = 0;
                b = rowA - 1;
                c = (a + b)/2 + 1;
                if (ctype( coorB1[i], coorB2[i], coorA1[a], coorA2[a]) == 0
                  || ctype( coorB1[i], coorB2[i], coorA1[b], coorA2[b]) == 0 ){
                        stateB[i] = 1;
                }
                while( a + 1 < b ){
                        if( ctype( coorB1[i], coorB2[i], coorA1[c], coorA2[c]) > 0){
                                a = c;
                                c = (a + b)/2;
                        }else if (ctype( coorB1[i], coorB2[i], coorA1[c], coorA2[c]) < 0){
                                b = c;
                                c = (a + b)/2;
                        }else{
                                stateB[i] = 1;
                                break;
                        }
                }
/*                if (stateB[i]==0)
                        fputs( buffer, B_A );
		else
			fputs( buffer, BA );
*/	}

	coorA1 = getcoor( fp1, column1[0], coorA1 );
        coorA2 = getcoor( fp1, column1[1], coorA2 );

        a = 0, b = rowA - 1;
        quicksort( coorA2, coorA1, a, b );

        for( i = 0, fseek( fp2, (long)0, SEEK_SET ); fgets( buffer, MAXWORD, fp2) != NULL; i++ ){
                a = 0;
                b = rowA - 1;
                c = (a + b)/2 + 1;
                if (ctype( coorB1[i], coorB2[i], coorA1[a], coorA2[a]) == 0 
                  || ctype( coorB1[i], coorB2[i], coorA1[b], coorA2[b]) == 0 ){
                        stateB[i] = 1;
                }
                while( a + 1 < b ){
                        if( ctype( coorB1[i], coorB2[i], coorA1[c], coorA2[c]) > 0){
                                a = c;
                                c = (a + b)/2;
                        }else if (ctype( coorB1[i], coorB2[i], coorA1[c], coorA2[c]) < 0){
                                b = c;
                                c = (a + b)/2;
                        }else{
                                stateB[i] = 1;
                                break;
                        }
                }
                if (stateB[i]==0)
                        fputs( buffer, B_A );
                else
                        fputs( buffer, BA );
        }

	free(coorA1);
	free(coorA2);
	free(coorB1);
	free(coorB2);
	free(stateA);
	free(stateB);

}

/* judge whether the coordinate has the intersection */
int ctype(int downA, int upA, int downB, int upB){
        if ( upA < downB ) 
                return -1;
	else if ( upB < downA )
		return 1;
        else
                return 0;
}

/* compare the file in option "-n" */
void ncmp( FILE *fp1, FILE *fp2, FILE *AB, FILE *BA, FILE *A_B, FILE *B_A, int *column1, int *column2 ){
        int rowA = count_row( fp1 );
        int rowB = count_row( fp2 );

        char **nameA = (char **)alloc(sizeof(char **)*(rowA+1));
        char **nameB = (char **)alloc(sizeof(char **)*(rowB+1));
	nameA = getname( fp1, column1[0], nameA );
	nameB = getname( fp2, column2[0], nameB );

	char *buffer = (char *)alloc( sizeof(char *)*MAXWORD );
	struct TreeNode *rootA, *rootB;
	rootA = create(); /* initialize the tree */
	
	int i;
	for( i = 0; i < rowB; i++ )
		insert(rootA, nameB[i]); /* insert the string into the tree */


	for( fseek(fp1, (long)0, SEEK_SET), i = 0;
	  fgets( buffer, MAXWORD, fp1 ) != NULL; i++ ){
		if ( search(rootA, nameA[i]) == 0) /* search in the tree */
			fputs( buffer, A_B);
		else
			fputs( buffer, AB );
	}

	delete(rootA); /* delete the tree */
	rootB = create();

	for( i = 0; i < rowA; i++ ){
		insert(rootB, nameA[i]);
	}
	for( fseek(fp2, (long)0, SEEK_SET), i = 0;
	  fgets( buffer, MAXWORD, fp2 ) != NULL; i++ ){
		if ( search(rootB, nameB[i]) == 0 )
                        fputs( buffer, B_A );
                else
                        fputs( buffer, BA );
	}

	delete(rootB);
	free(buffer);
	free(nameA);
	free(nameB);
}
