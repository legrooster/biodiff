#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"norc.c"
#include"column.c"
#include"getcolumn.c"

#define A_COLUMN  3
#define B_COLUMN  5
#define FROM   6   /* the sequence of the argument */
#define TO     7

void ccmp( FILE *fp1, FILE *fp2, FILE *AB, FILE *BA, FILE *A_B, FILE *B_A, int *column1, int *column2 );

int main( int argc, char *argv[]){
/* read the column that should be recorded */
	int column1[2], column2[2];
	column( argc, argv, A_COLUMN, column1 );
	column( argc, argv, B_COLUMN, column2 );

	FILE *fp1, *fp2;
/* open the file and judge if the file exists */
        fp1 = fopen( argv[FROM], "r");
        if (fp1 == NULL){
                perror("fopen");
                exit(EXIT_FAILURE);
        }

        fp2 = fopen( argv[TO], "r");
        if (fp2 == NULL){
                perror("fopen");
                exit(EXIT_FAILURE);
        }
/* ensure if the file is read successfully */

/* open the output file in "write" mode */
        static FILE *AB;
        static FILE *BA;
        static FILE *A_B;
        static FILE *B_A;
        AB = fopen("AB.out", "w");
        BA = fopen("BA.out", "w");
        A_B = fopen("A-B.out", "w");
        B_A = fopen("B-A.out", "w");

	if (norc(argc, argv) > 0)
		ccmp(fp1, fp2, AB, BA, A_B, B_A, column1, column2);
	else if(norc(argc, argv) < 0)
		ncmp(fp1, fp2, AB, BA, A_B, B_A, column1, column2);

        fclose(fp1);
        fclose(fp2);
	fclose(AB);
	fclose(BA);
	fclose(A_B);
	fclose(B_A);

}
