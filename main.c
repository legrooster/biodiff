#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"head.h"

#define FROM   6   /* the sequence of the argument */
#define TO     7

int main(int argc, char **argv)
{
/* read the column contain the data you want */
	int column1[2], column2[2];
	column(argc, argv, A_COLUMN, column1);
  	column(argc, argv, B_COLUMN, column2);

/* read the objective file */
  	FILE *fp1, *fp2, *fp3;

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
	

	if (norc(argc, argv) > 0){
/* firstly, get there output files */
		ccmp(fp1, fp2, AB, BA, A_B, column1, column2);
		fclose(AB);
		fclose(BA);
		fclose(A_B);
		fp3 = fopen("A-B.out","r");
		if (fp3 == NULL){
			perror("fopen(A-B.out)");
			exit(EXIT_FAILURE);
		}
/* secondly, get the last files */
		reccmp(fp2, fp3, B_A, column2);
		fclose(B_A);

/* the same way as the former method */
	}else if( norc(argc, argv)<0 ){
		ncmp(fp1, fp2, AB, BA, A_B, column1, column2);
                fclose(AB);
                fclose(BA);
                fclose(A_B);
                fp3 = fopen("A-B.out","r");
                if (fp3 == NULL){
                        perror("fopen(A-B.out)");
                        exit(EXIT_FAILURE);
		}
		rencmp(fp2, fp3, B_A, column2);
		fclose(B_A);
	}

 	printf("o98k\n");
  	fclose(fp1);
  	fclose(fp2);
	fclose(fp3);
  	return 0;
}

