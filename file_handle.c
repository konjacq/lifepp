#include "file_handle.h"
#include <time.h>
#include <string.h>
double mathch_value[26][26];


void matit()
{
	mathch_value[0][0] = 10;
	mathch_value[0][6] = -1;
	mathch_value[0][2] = -3;
	mathch_value[0][19] = -4;

	mathch_value[6][0] = -1;
	mathch_value[6][6] = 9;
	mathch_value[6][2] = -5;
	mathch_value[6][19] = -3;

	mathch_value[2][0] = -3;
	mathch_value[2][6] = -5;
	mathch_value[2][2] = 9;
	mathch_value[2][19] = 0;

	mathch_value[19][0] = -4;
	mathch_value[19][6] = -3;
	mathch_value[19][2] = 0;
	mathch_value[19][19] = 8;

}

int init_file()
{
	if (newpro == 0)
		return 0;
	tot = 0;
	FILE *cof = fopen("config.lifepp", "r");

	if (cof == NULL)
	{
		rec_file();
	}
	fclose(cof);
	cof = fopen("config.lifepp", "r");

	tot = fgetc(cof) - 48;
	//printf("%d", tot);
	//fgetc(cof);
	char str;
	int t = -1, p = 0;
	while ((str = fgetc(cof)) != EOF)
	{
		if (str == '\n' && t < tot)
		{
			t++;
			p = 0;
		}
		else
		{
			all_file[t][p++] = str;
			all_file[t][p] = '\0';
		}
	}
	for (int i = 0; i < tot; i++)
	{
		FILE *pf = fopen(all_file[i], "r");
		if (pf == NULL)
		{

			tot = 0;
			rec_file();
			return 1;

		}
		handle_seq(pf, i);
		fclose(pf);
	}
	fclose(cof);
	return 0;
	//fclose(pf);
}


void cr_file()
{
	tot = 0;
	FILE *cof = fopen("config.lifepp", "r");
	fclose(cof);
	if (cof == NULL)
	{
		rec_file();
	}
	cof = fopen("config.lifepp", "r");
	tot = fgetc(cof) - 48;
	//printf("%d", tot);
	//fgetc(cof);
	char str;
	int t = -1, p = 0;
	while ((str = fgetc(cof)) != EOF)
	{
		if (str == '\n' && t < tot)
		{
			t++;
			p = 0;
			//printf("%d", t);
		}
		else
		{
			all_file[t][p++] = str;
			all_file[t][p] = '\0';
		}
	}
	int real = 0;
	FILE *ppf = fopen("config.lifeppp", "w");
	fputc('\n', ppf);
	for (int i = 0; i < tot; i++)
	{
		FILE *pf = fopen(all_file[i], "r");
		//FILE *ppf = fopen("config.lifeppp", "w");
		if (pf != NULL)
		{
			for (int j = 0; j < (int)strlen(all_file[i]); j++)
			{
				fputc(all_file[i][j], ppf);
			}
			fputc('\n', ppf);
			real++;
		}
		//handle_seq(pf, i);
		fclose(pf);
	}
	fseek(ppf, 0, SEEK_SET);
	fputc(real + 48, ppf);
	fclose(ppf);
	fclose(cof);
	remove("config.lifepp");
	rename("config.lifeppp", "config.lifepp");
	cof = fopen("config.lifepp", "r");
	tot = fgetc(cof) - 48;

	t = -1;
	p = 0;
	while ((str = fgetc(cof)) != EOF)
	{
		if (str == '\n' && t < tot)
		{
			t++;
			p = 0;
		}
		else
		{
			all_file[t][p++] = str;
			all_file[t][p] = '\0';
			//printf("%s\n", all_file[t]);
		}
	}
	for (int i = 0; i < tot; i++)
	{
		FILE *pf = fopen(all_file[i], "r");
		//FILE *ppf = fopen("config.lifeppp", "w");
		if (pf != NULL)
		{
			for (int j = 0; j < (int)strlen(all_file[i]); j++)
			{
				fputc(all_file[i][j], ppf);
			}
			fputc('\n', ppf);
			real++;
		}
		handle_seq(pf, i);
		fclose(pf);
	}



	fclose(cof);
	return ;
	//fclose(pf);
}

void rec_file()
{
	remove("config.lifepp");
	FILE *cof = fopen("config.lifepp", "w");
	fputc(tot + 48, cof);
	fputc('\n', cof);
	for (int i = 0; i < tot; i++)
	{
		for (int j = 0; j < (int)strlen(all_file[i]); j++)
		{
			//printf("%c", all_file[i][j]);
			fputc(all_file[i][j], cof);
		}
		fputc('\n', cof);
	}
	fclose(cof);
}

int handle_seq(FILE *seq, int curr)
{
	char first = fgetc(seq), str;
	int s = 0, k1 = 0, k2 = 0;
	if (first != '>')
		return 1;//pls input standard fasta file
	//char *s1 = curr.identifier;
	//char *s2 = curr.sequence;
	all_sp[nw].identifier = all_id[nw];
	memset(all_id, '\0', sizeof(all_id));
	//all_sp[curr].sequence = all_seq[curr];
	char all_seq[100000];
	while ((str = fgetc(seq)) != EOF)
	{
		if (!((str >= 48 && str <= 57) || (str >= 65 && str < 90) || (str >= 97 && str <= 122) || str == '\n' || str == 32
		        || str == '.' || str == ',' || str == '#' || str == ':'))
		{
			break;
		}
		//printf("%c", str);
		if (str == '\n')
			s = 1;
		if (s == 0)
		{
			all_sp[nw].identifier[k1++] = str;
		}
		else if (s == 1 && str != '\n' && str != 32)
		{
			all_seq[k2++] = str;
		}
	}
	all_sp[nw].identifier[k1] = '\0';
	all_seq[k2] = '\0';
	//printf("%s", all_seq);
	int rec = species_insert(all_sp[nw].identifier, all_seq);
	//printf("%s\n", all_sp[nw].identifier);
	trans_table[rec] = curr;
	//printf("%d %d\n", rec, curr);
	return 0;//opr success
}


char *file_copy(char route[], int curr)
{
	FILE *pf = fopen(route, "r");
	if (pf == NULL)
		return NULL;//file not exist
	int finax = -1;
	for (int i = 0; i < (int)strlen(route); i++)
	{
		if (route[i] == '/')
			finax = i;
	}
	static char targ[100000];
	memset(targ, '\0', sizeof(targ));
	int lent = 0;
	for (int i = finax + 1; i < (int)strlen(route); i++)
	{
		targ[lent++] = route[i];
	}
	if (finax == -1)
	{
		fclose(pf);
		return targ;
	}
	char op[100000];
	memset(op, '\0', sizeof(op));
	time_t timer;
	time(&timer);
	strcat(op, "_seq_");
	strcat(op, ctime(&timer));
	op[strlen(op) - 1] = '.';
	strcat(op, "fasta");
	//printf("%s", op);
	for (int i = 0; i < (int) strlen(op); i++)
	{
		if (op[i] == ':')
			op[i] = '.';
	}
	strcat(targ, op);
	//op[0] = '\0';
	//targ[lent] = '\0';
	//printf("%s", targ);
	char str;
	FILE *pft = fopen(targ, "w");
	while ((str = fgetc(pf)) != EOF)
	{
		fputc(str, pft);
	}
	fclose(pf);
	fclose(pft);
	for (int i = 0; i < (int)strlen(targ); i++)
	{
		all_file[curr][i] = targ[i];
	}
	all_file[curr][strlen(targ)] = '\0';
	rec_file();
	return targ;
}

int seq_del(int now)
{

	int k = remove(all_file[now]);
	//printf("%s", all_file[now]);
	if (k != 0)
		return 1;
	return 0;
}

int add_seq(char route[], char all_filename[][100000], int *n)
{
	(*n) = (*n) + 1;
	FILE *pf;
	if ((pf = fopen(route, "r")) == NULL)
		return 1;//file not exist
	fclose(pf);
	strcpy(all_filename[(*n)], file_copy(route, (*n)));
	pf = fopen(all_filename[(*n)], "r");
	if (handle_seq(pf, (*n)))
		return 1;
	return 0;
}

/*
int main()
{

	return 0;
}*/
