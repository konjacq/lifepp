#include <stdlib.h>
#include <string.h>
#include "heap.h"

int heap_size;
edge *heap_root;

int edge_compare(edge *u,edge *v) {
	/* return double_compare(u->length,v->length); */
	return u->length==v->length?0:(u->length<v->length?-1:1);
}

void edge_swap(edge *u,edge *v) {
	int w; double x;
	w=u->node_u; u->node_u=v->node_u; v->node_u=w;
	w=u->node_v; u->node_v=v->node_v; v->node_v=w;
	x=u->length; u->length=v->length; v->length=x;
}

void heap_pushdown(edge *u) {
	while (u->less_son!=NULL) {
		if (edge_compare(u,u->less_son)==1) {
			edge_swap(u,u->less_son); u=u->less_son;
			if (u->father->greater_son!=NULL&&edge_compare(u,u->father->greater_son)==1) {
				edge_swap(u,u->father->greater_son); u=u->father->greater_son;
				heap_pushdown(u->father->less_son);
			}
		}
		else return;
	}
}

void heap_pushup(edge *u) {
	while (u->father!=NULL) {
		if (edge_compare(u,u->father)==-1) {
			edge_swap(u,u->father); u=u->father;
			if (u->greater_son!=NULL&&edge_compare(u->less_son,u->greater_son)==1)
				edge_swap(u->less_son,u->greater_son);
		}
		else {
			if (u->father!=NULL&&edge_compare(u,u->father->less_son)==-1)
				edge_swap(u,u->father->less_son);
			return;
		}
	}
}

void heap_push(edge *u) {
	if (!(heap_size++)) {
		heap_root=u; return;
	}
	int v=heap_size,w=1; edge *x=heap_root;
	while (v>=w) w<<=1; w>>=2;
	while (w>1) {
		if (v&w) x=x->greater_son;
		else x=x->less_son; w>>=1;
	}
	if (v&1) x->greater_son=u;
	else x->less_son=u; u->father=x;
	heap_pushup(u);
	
}

edge heap_top() { return *heap_root; }

int heap_empty() { return heap_size?0:1; }

void heap_pop() {
	if (heap_size==1) {
		free(heap_root); heap_size=0; return;
	}
	int v=heap_size--,w=1; edge *x=heap_root;
	while (v>=w) w<<=1; w>>=2;
	while (w) {
		if (v&w) x=x->greater_son;
		else x=x->less_son; w>>=1;
	}
	heap_root->node_u=x->node_u;
	heap_root->node_v=x->node_v;
	heap_root->length=x->length;
	if (v&1) x->father->greater_son=NULL;
	else x->father->less_son=NULL;
	free(x);
	heap_pushdown(heap_root);
}
