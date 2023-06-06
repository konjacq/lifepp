#ifndef BLOCK_LIST_H
#define BLOCK_LIST_H

#include "backend.h"

#define block_size 50

block *block_list_create(double *u,int v);
void block_list_insert(block *u,double v,int w);
void block_list_modify(block *u,double v,int w);
void block_list_remove(block *u,int v);
void block_list_to_double(block *u,double *v);
void free_block_list(block *u);

#endif
