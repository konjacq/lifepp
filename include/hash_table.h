#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "backend.h"

extern int hash_table_size;

hash_node *hash_table_find(char *u);
hash_node *hash_table_find_by_number(int u);
/* int hash_table_subscript_by_species(species *u); */
/* int hash_table_subscript_by_hash_table(hash_node *u); */
int hash_table_insert(species *u);
void hash_table_remove(hash_node *u);

#endif
