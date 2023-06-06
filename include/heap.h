#ifndef HEAP_H
#define HEAP_H

#include "backend.h"

void heap_push(edge *u);
edge heap_top();
int heap_empty();
void heap_pop();

#endif
