/* include all the functions and the declarations */

#include"alloc.c"
#include"column.c"
#include"norc.c"
#include"ncmp.c"
#include"ccmp.c"
#include"ctype.c"
#include"ntype.c"
#include"reccmp.c"
#include"rencmp.c"

#define FROM   6   /* the sequence of the argument */
#define TO     7

int norc(int argc, char **argv);
void column(int argc, char **argv, int num, int *column_num);
void ccmp(FILE *fp1, FILE *fp2,
  FILE *AB, FILE *BA, FILE *A_B,
  int *column1, int *column2);
void ncmp(FILE *fp1, FILE *fp2,
  FILE *AB, FILE *BA, FILE *A_B,
  int *column1, int *column2);
void reccmp(FILE *fp2, FILE *fp3, FILE *B_A, int *column2);
void rencmp(FILE *fp2, FILE *fp3, FILE *B_A, int *column2);

