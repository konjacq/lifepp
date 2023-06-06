#include <stdlib.h>
#include "block_list.h"

block *block_list_create(double *u,int v) {
	block *w=(block*)malloc(sizeof(block)),*x,*y; x=y=w;
	for (int i=0;i<v;i+=block_size) {
		if (i) w=(block*)malloc(sizeof(block));
		w->value=(double*)malloc(sizeof(double)*(w->size=imin(block_size,v-i)));
		for (int j=0;j<w->size;++j) w->value[j]=u[i+j];
		(w->prev=y)->next=w; y=w;
	}
	x->prev=y->next=NULL; return x;
}

void block_list_insert(block *u,double v,int w) {
	if (!u->size) {
		u->value=(double*)malloc(sizeof(double));
		u->value[0]=v; u->size=1;
		return;
	}
	for (;u->next!=NULL&&u->size<=w;u=u->next) w-=u->size;
	double *x=(double*)malloc(sizeof(double)*(u->size+1));
	for (int i=0;i<w;++i) x[i]=u->value[i];
	for (int i=w;i<u->size;++i) x[i+1]=u->value[i];
	free(u->value); (u->value=x)[w]=v;
	if ((++u->size)>(block_size<<1)) {
		x=(double*)malloc(sizeof(double)*block_size);
		double *y=(double*)malloc(sizeof(double)*(u->size-block_size));
		for (int i=0;i<block_size;++i) x[i]=u->value[i];
		for (int i=block_size;i<u->size;++i) y[i-block_size]=u->value[i];
		block *z=(block*)malloc(sizeof(block));
		z->value=y; z->size=u->size-block_size;
		if ((z->next=(z->prev=u)->next)!=NULL) z->next->prev=z;
		u->next=z;
		free(u->value); u->value=x; u->size=block_size;
	}
}

void block_list_modify(block *u,double v,int w) {
	for (;u->size<=w;u=u->next) w-=u->size;
	u->value[w]=v;
}

void block_list_remove(block *u,int v) {
	for (;u->size<=v;u=u->next) v-=u->size;
	double *w=(double*)malloc(sizeof(double)*(u->size-1));
	for (int i=0;i<v;++i) w[i]=u->value[i];
	for (int i=v+1;i<u->size;++i) w[i-1]=u->value[i];
	free(u->value); u->value=w; --u->size;
	if (u->next!=NULL&&u->size+u->next->size<block_size) {
		int x=0;
		w=(double*)malloc(sizeof(double)*(u->size+u->next->size));
		for (int i=0;i<u->size;++i) w[x++]=u->value[i];
		for (int i=0;i<u->next->size;++i) w[x++]=u->value[i];
		free(u->value); u->value=w;
		u->size+=u->next->size;
		if ((u->next=u->next->next)!=NULL) u->next->prev=u;
		free(u->next->value); free(u->next);
	}
}

void block_list_to_double(block *u,double *v) {
	int w=0; for (;u!=NULL;u=u->next)
		for (int j=0;j<u->size;++j) v[w++]=u->value[j];
}

void free_block_list(block *u) {
	block *v;
	while (u!=NULL) {
		v=u->next;
		free(u);
		u=v;
	}
}
