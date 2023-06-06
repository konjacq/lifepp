#ifndef BACKEND_H
#define BACKEND_H

#include "connector.h"

typedef struct edge_this {
	int node_u,node_v;
	struct edge_this *father,*less_son,*greater_son;
	double length;
} edge;

#include "hash_table.h"
#include "block_list.h"
#include "heap.h"
#include "queue.h"

int imin(int u,int v);
int imax(int u,int v);
int str_compare(char *u,char *v);
int double_compare(double u,double v);

#endif
