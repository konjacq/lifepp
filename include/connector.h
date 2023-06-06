#ifndef CONNECTOR_H
#define CONNECTOR_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct block_this {
	int size;
	double *value;
	struct block_this *prev,*next;
} block;
typedef struct {
	char *identifier,*sequence;
	block *distance;
} species;
typedef struct {
	int size,root_size,*root,*left_son,*right_son;
	double *edge_length;
	species **node;
} tree;
typedef struct hash_node_this {
	int key_main,modified,number;
	unsigned long long key_0,key_1,key_2;
	species *node;
	struct hash_node_this *prev,*next;
} hash_node;

species *find_species(char *identifier);
int species_insert(char *identifier,char *sequence);
int species_modify(char *identifier,char *sequence);
int species_remove(char *identifier);
int species_remove_by_number(int number);
void free_tree(tree *operated_on);
tree build_tree(double match_value[][26],double blank_value,double max_distance);
hash_node *hash_table_begin();
hash_node *hash_table_next(hash_node *current_node);
hash_node *hash_table_cycle_next(hash_node *current_node);

#ifdef __cplusplus
}
#endif

#endif
