#ifndef FILE_HANDLE_H
#define FILE_HANDLE_H
#include <stdio.h>
#include <string.h>
#include "connector.h"

/*typedef struct
{
	char *identifier, *sequence;
	void *distance;
} species;*/
extern species all_sp[2];
extern char all_id[2][1000];
//extern char all_seq[10000][10000];
extern int tot;
extern char all_file[10000][1000];
extern int trans_table[10000];
extern double mathch_value[26][26];
extern int nw;
extern int newpro;
//extern FILE *cof;
//species a;

#ifdef __cplusplus
extern "C" {
#endif

int handle_seq(FILE *seq, int curr);
char *file_copy(char route[], int curr);
int seq_del(int now);
int add_seq(char route[], char all_filename[][100000], int *n);
int init_file();
void rec_file();
void cr_file();
void matit();

#ifdef __cplusplus
}
#endif

#endif
