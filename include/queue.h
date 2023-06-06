#ifndef QUEUE_H
#define QUEUE_H

#include "backend.h"

typedef struct queue_node_this {
	int number;
	struct queue_node_this *next;
} queue_node;

extern int max_number;

int next_number();
void remove_number(int u);

#endif
