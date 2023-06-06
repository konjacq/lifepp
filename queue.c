#include <stdlib.h>
#include "queue.h"

int max_number;
queue_node *queue_head,*queue_tail;

int next_number() {
	if (!queue_head) return ++max_number;
	int u=queue_head->number;
	queue_node *v=queue_head->next;
	free(queue_head); queue_head=v;
	return u;
}

void remove_number(int u) {
	if (!queue_head) {
		queue_head=queue_tail=(queue_node*)malloc(sizeof(queue_node));
		queue_head->number=u;
		queue_head->next=NULL;
	}
	else {
		queue_node *v=(queue_node*)malloc(sizeof(queue_node));
		(queue_tail->next=v)->next=NULL;
		(queue_tail=v)->number=u;
	}
}
