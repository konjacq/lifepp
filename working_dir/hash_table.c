#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

/* 树状数组求 hash_table 内位置, 这部分接口不开放 */

/*
int fenwick_tree[hash_table_max_size+1];

int lowbit(int u) {return u&(-u);}

int fenwick_tree_query(int u) {
	int v=0;
	for (++u;u;u-=lowbit(u)) v+=fenwick_tree[u];
	return v;
}

void fenwick_tree_add(int u) {
	for (++u;u<=hash_table_max_size;u+=lowbit(u))
		++fenwick_tree[u];
}

void fenwick_tree_dec(int u) {
	for (++u;u<=hash_table_max_size;u+=lowbit(u))
		--fenwick_tree[u];
}
*/

#define hash_table_max_size 100007
#define hash_base_main 131
#define hash_base_0 31
#define hash_mod_0 1610612741ull
#define hash_base_1 37
#define hash_mod_1 3221225473ull
#define hash_base_2 53
#define hash_mod_2 4294967291ull

int hash_table_size,head_used_position[hash_table_max_size],number_to_hash_node_size;
hash_node *head[hash_table_max_size],*head_used[hash_table_max_size];
hash_node **number_to_hash_node;

void resize_number_to_hash_node(int u) {
	hash_node **v=(hash_node**)malloc(sizeof(hash_node*)*u);
	if (number_to_hash_node_size) {
		memcpy(v,number_to_hash_node,sizeof(hash_node*)*imin(number_to_hash_node_size+1,u));
		free(number_to_hash_node);
	}
	number_to_hash_node_size=u;
	number_to_hash_node=v;
}

hash_node *hash_table_begin() {
	int u=0;
	for (int i=0;i<hash_table_max_size;++i) if (head[i]!=NULL)
		head_used[head_used_position[i]=u++]=head[i];
	head_used[u]=NULL;
	return head_used[0];
}

hash_node *hash_table_next(hash_node *current_node) {
	if (current_node->next!=NULL) return current_node->next;
	return head_used[head_used_position[current_node->key_main]+1];
}

/*
hash_node *hash_table_next(hash_node *current_node) {
	if (current_node->next!=NULL) return current_node->next;
	for (int i=current_node->key_main+1;i<hash_table_max_size;++i)
		if (head[i]!=NULL) return head[i];
	return NULL;
}
*/

hash_node *hash_table_cycle_next(hash_node *current_node) {
	/* 没有改写, 能不用就不要用 */
	if (current_node->next!=NULL) return current_node->next;
	int u=current_node->key_main+1; if (u>=hash_table_max_size) u=0;
	while (u!=current_node->key_main) {
		if (head[u]!=NULL) return head[u];
		if ((++u)>=hash_table_max_size) u=0;
	}
	return NULL;
}

/*
int char_to_int(char u) {
	if (u>='A'&u<='Z') return u-'A';
	else if (u>='a'&u<='z') return u-'a'+26;
	else return u-'0'+52;
}

int str_hash(char *u) {
	int v=0;
	for (;*u;++u) v=(v*hash_base+char_to_int(*u))%hash_table_max_size;
	return v;
}
*/

void str_calculate_key(char *u,hash_node *v) {
	v->key_main=0; v->key_0=v->key_1=v->key_2=0;
	for (;*u;++u) {
		v->key_main=(v->key_main*hash_base_main+(*u))%hash_table_max_size;
		v->key_0=(v->key_0*hash_base_0+(*u))%hash_mod_0;
		v->key_1=(v->key_1*hash_base_1+(*u))%hash_mod_1;
		v->key_2=(v->key_2*hash_base_2+(*u))%hash_mod_2;
	}
}

hash_node *hash_table_find(char *u) {
	hash_node v;
	str_calculate_key(u,&v);
	for (hash_node *i=head[v.key_main];i!=NULL;i=i->next)
		if (v.key_0==i->key_0&&v.key_1==i->key_1&&v.key_2==i->key_2) return i;
	return NULL;
}

hash_node *hash_table_find_by_number(int u) {
	if (number_to_hash_node_size<u) return NULL;
	return number_to_hash_node[u];
}

/*
int hash_table_subscript_by_species(species *u) {
	int v=fenwick_tree_query(str_hash(u->identifier)-1);
	for (hash_node *i=head[v];i;i=i->next,++v)
		if (!str_compare(u->identifier,i->node->identifier)) return v;
}

int hash_table_subscript_by_hash_node(hash_node *u) {
	int v=fenwick_tree_query(u->key-1);
	for (hash_node *i=head[v];i;i=i->next,++v)
		if (u->node==i->node) return v;
}
*/

int hash_table_insert(species *u) {
	hash_node *v=(hash_node*)malloc(sizeof(hash_node));
	/* v->key=str_hash(u->identifier); */
	str_calculate_key(u->identifier,v);
	v->modified=2; v->number=next_number();
	v->node=u; v->next=NULL;
	if (head[v->key_main]==NULL) (head[v->key_main]=v)->prev=NULL;
	else {
		hash_node *w=head[v->key_main];
		while (w->next!=NULL) w=w->next;
		(v->prev=w)->next=v;
	}
	++hash_table_size;
	if (max_number>=number_to_hash_node_size)
		resize_number_to_hash_node(max_number<<1);
	/*
	if (max_number<number_to_hash_node_size>>2)
		resize_number_to_hash_node(max_number>>1);
	*/
	number_to_hash_node[v->number]=v;
	return v->number;
	/*
	将修改 dis 移动至建树前 
	fenwick_tree_add(v->key);
	return fenwick_tree_query(v->key)-1;
	*/
}

void hash_table_remove(hash_node *u) {
	if (u->prev!=NULL) u->prev->next=u->next;
	else head[u->key_main]=u->next;
	if (u->next!=NULL) u->next->prev=u->prev;
	number_to_hash_node[u->number]=NULL;
	remove_number(u->number);
	free(u->node->identifier);
	free_block_list(u->node->distance);
	free(u->node); free(u);
	--hash_table_size;
}
