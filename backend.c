#include <stdlib.h>
#include <string.h>
#include "backend.h"

int *dsu_father;
double **node_distance;

int imin(int u, int v)
{
	return u < v ? u : v;
}

int imax(int u, int v)
{
	return u > v ? u : v;
}

char *str_copy(char *u)
{
	char *v = u, *w;
	for (; *v; ++v);
	w = (char *)malloc(sizeof(char) * (v - u + 1));
	memcpy(w, u, sizeof(char) * (v - u + 1));
	return w;
}

int str_compare(char *u, char *v)
{
	for (; (*u) || (*v); ++u, ++v)
	{
		if (!(*u) || (*u) < (*v))
			return -1;
		else if (!(*v) || (*u) > (*v))
			return 1;
	}
	return 0;
}

double str_calculate(char *u, char *v, double w[][26], double x)
{
	int n = 0, m = 0;
	double **f, g = 0;
	for (; u[n]; ++n)
		;
	for (; v[m]; ++m);
	f = (double **)malloc(sizeof(double *)*n);
	for (int i = 0; i < n; ++i)
		f[i] = (double *)malloc(sizeof(double) * m);
	f[0][0] = imax(w[u[0] - 65][v[0] - 65], 0);
	for (int i = 1; i < n; ++i)
		f[i][0] = imax(imax(w[u[i] - 65][v[0] - 65], 0), f[i - 1][0] + x);
	for (int i = 1; i < m; ++i)
		f[0][i] = imax(imax(w[u[0] - 65][v[i] - 65], 0), f[0][i - 1] + x);
	for (int i = 1; i < n; ++i)
		for (int j = 1; j < m; ++j)
			f[i][j] = imax(imax(f[i - 1][j - 1] + w[u[i] - 65][v[i] - 65], 0), imax(f[i - 1][j], f[i][j - 1]) + x);
	for (int i = 0; i < n; ++i)
		g += 0.5 * w[u[i] - 65][u[i] - 65];
	for (int i = 0; i < m; ++i)
		g += 0.5 * w[v[i] - 65][v[i] - 65];
	g = 1 - f[n - 1][m - 1] / g;
	for (int i = 0; i < n; ++i)
		free(f[i]);
	free(f);
	return g;
}

species *find_species(char *identifier)
{
	hash_node *v = hash_table_find(identifier);
	return v == NULL ? NULL : v->node;
	/*
	旧版本实现, 已移动至 hash_table.c
	int v=str_hash(identifier);
	for (hash_node *i=head[v];i;i=i->next)
		if (!str_compare(identifier,i->node->identifier)) return i->node;
	return NULL;
	*/
}

edge *make_edge(int u, int v)
{
	edge *w = (edge *)malloc(sizeof(edge));
	w->node_u = u;
	w->node_v = v;
	w->father = w->less_son = w->greater_son = NULL;
	w->length = node_distance[u][v];
	return w;
}

/*
edge make_edge(int u,int v) {
	edge w; w.node_u=u; w.node_v=v;
	w.length=node_distance[u][v]; return w;
}
*/

int dsu_find(int u)
{
	return u == dsu_father[u] ? u : (dsu_father[u] = dsu_find(dsu_father[u]));
}

int double_compare(double u, double v)
{
	return (u -= v) < -1e-6 ? -1 : (u > 1e-6 ? 1 : 0);
}

int species_insert(char *identifier, char *sequence)
{
	hash_node *u = hash_table_find(identifier);
	if (u != NULL)
	{
		if (u->modified & 4)
		{
			u->node->sequence = str_copy(sequence);
			u->modified = 1; /* 标记 2 与 4 不共存 */
			return u->number;
		}
		else
			return u->number;
	}
	species *v = (species *)malloc(sizeof(species));
	v->identifier = str_copy(identifier);
	v->sequence = str_copy(sequence);
	v->distance = (block *)malloc(sizeof(block));
	v->distance->size = 0;
	v->distance->next = v->distance->prev = NULL;
	return hash_table_insert(v);
}

int species_modify(char *identifier, char *sequence)
{
	hash_node *u = hash_table_find(identifier);
	if (u == NULL || (u->modified & 4))
		return -1;
	free(u->node->sequence);
	u->node->sequence = str_copy(sequence);
	u->modified |= 1;
	return u->number;
}

int species_remove_by_hash_node(hash_node *u)
{
	/* 标记 2 与 4 不共存 */
	if (u->modified & 4)
		return -1;
	else if (u->modified & 2)
	{
		free(u->node->sequence);
		hash_table_remove(u);
	}
	else
	{
		free(u->node->sequence);
		u->modified |= 4;
	}
	return 0;
}

int species_remove(char *identifier)
{
	hash_node *u = hash_table_find(identifier);
	if (u == NULL)
		return -1;
	return species_remove_by_hash_node(u);
}

int species_remove_by_number(int number)
{
	hash_node *u = hash_table_find_by_number(number);
	if (u == NULL)
		return -1;
	return species_remove_by_hash_node(u);
}

void free_tree(tree *operated_on)
{
	free(operated_on->left_son);
	free(operated_on->right_son);
	free(operated_on->node);
	free(operated_on->edge_length);
	free(operated_on->root);
}

#define tree_size hash_table_size

void rearrangement_subtree(tree *u, int *v, int w)
{
	int x;
	if (u->left_son[w] != -1)

	{
		rearrangement_subtree(u, v, u->left_son[w]);
		rearrangement_subtree(u, v, u->right_son[w]);
		if (u->left_son[u->left_son[w]] != -1)
		{
			if (double_compare(node_distance[v[u->left_son[u->left_son[w]]]][v[u->right_son[w]]],
			                   node_distance[v[u->right_son[u->left_son[w]]]][v[u->right_son[w]]]) == -1)
			{
				x = u->left_son[u->left_son[w]];
				u->left_son[u->left_son[w]] = u->right_son[u->left_son[w]];
				u->right_son[u->left_son[w]] = x;
			}
		}
		if (u->left_son[u->right_son[w]] != -1)
		{
			if (double_compare(node_distance[v[u->left_son[w]]][v[u->left_son[u->right_son[w]]]],
			                   node_distance[v[u->left_son[w]]][v[u->right_son[u->right_son[w]]]]) == 1)
			{
				x = u->left_son[u->right_son[w]];
				u->left_son[u->right_son[w]] = u->right_son[u->right_son[w]];
				u->right_son[u->right_son[w]] = x;
			}
		}
		v[w] = v[u->left_son[w]];
		for (int i = 0; i < tree_size; ++i)
			node_distance[v[w]][i] = node_distance[i][v[w]] = 0.5 * (node_distance[v[w]][i] + node_distance[v[u->right_son[w]]][i]);
	}
}

tree build_tree(double match_value[][26], double blank_value, double max_distance)
{
	tree result;
	result.root_size = 0;
	result.left_son = (int *)malloc(sizeof(int) * ((result.size = tree_size) << 1));
	result.right_son = (int *)malloc(sizeof(int) * (tree_size << 1));
	result.edge_length = (double *)malloc(sizeof(double) * (tree_size << 1));
	result.node = (species **)malloc(sizeof(species **) * (tree_size << 1));
	memset(result.left_son, 0xff, sizeof(int) * (tree_size << 1));
	memset(result.right_son, 0xff, sizeof(int) * (tree_size << 1));


	{
		/* dis 计算 */
		double *u = (double *)malloc(sizeof(double) * (hash_table_size));
		int v, w;
		for (hash_node *i = hash_table_begin(); i != NULL;)
		{
			if (i->modified)
			{
				v = w = 0;
				for (hash_node *j = hash_table_begin(); j != NULL && i->node != j->node; j = hash_table_next(j))
					if (!(j->modified & 2))
						++v;
				if (i->modified & 4)
				{
					hash_node *x = i;
					for (hash_node *j = hash_table_begin(); j != NULL; j = hash_table_next(j))
						if (!(j->modified & 6))
							block_list_remove(j->node->distance, v);
					i = hash_table_next(i);
					hash_table_remove(x);
				}
				else if (i->modified & 2)
				{
					for (hash_node *j = hash_table_begin(); j != NULL; j = hash_table_next(j))
					{
						if (!(j->modified & 6))
						{
							u[w] = str_calculate(i->node->sequence, j->node->sequence, match_value, blank_value);
							block_list_insert(j->node->distance, u[w++], v);
						}
						else if (i->node == j->node)
							u[w++] = 0;
					}
					i->node->distance = block_list_create(u, w);
					i->modified = 0;
					i = hash_table_next(i);
				}
				else if (i->modified & 1)
				{
					for (hash_node *j = hash_table_begin(); j != NULL; j = hash_table_next(j))
					{
						if ((!(j->modified & 6)) && i->node != j->node)
						{
							u[w] = str_calculate(i->node->sequence, j->node->sequence, match_value, blank_value);
							block_list_modify(j->node->distance, u[w++], v);
						}
						else if (i->node == j->node)
						{
							block_list_modify(i->node->distance, u[w] = 0, w);
							++w;
						}
					}
					i->modified = 0;
					i = hash_table_next(i);
				}
			}
			else
				i = hash_table_next(i);
		}
		free(u);
	}
	{
		/* 建边长矩阵, 建叶节点 */
		int u = 0;
		node_distance = (double **)malloc(sizeof(double *)*tree_size);
		for (int i = 0; i < tree_size; ++i)
		{
			node_distance[i] = (double *)malloc(sizeof(double) * tree_size);
			result.node[tree_size + i] = NULL;
		}
		for (hash_node *i = hash_table_begin(); i != NULL; i = hash_table_next(i))
		{
			block_list_to_double(i->node->distance, node_distance[u]);
			result.node[u++] = i->node;
		}
		while (!heap_empty())
			heap_pop();
		for (int i = 0; i < tree_size; ++i)
			for (int j = i + 1; j < tree_size; ++j)
				heap_push(make_edge(i, j));
	}
	{
		/* 建树 */
		edge u;
		int v, w, *x = (int *)malloc(sizeof(int) * tree_size);
		dsu_father = (int *)malloc(sizeof(int) * tree_size);
		for (int i = 0; i < tree_size; ++i)
			dsu_father[i] = x[i] = i;
		while (!heap_empty())
		{
			do
			{
				u = heap_top();
				heap_pop();
				v = dsu_find(u.node_u);
				w = dsu_find(u.node_v);
			}
			while ((!heap_empty()) && (double_compare(u.length, node_distance[v][w]) || v == w));
			if (double_compare(u.length, node_distance[v][w]) || v == w || double_compare(node_distance[v][w], max_distance) == 1)
				break;
			result.left_son[result.size] = x[v];
			result.right_son[x[dsu_father[w] = v] = result.size] = x[w];
			result.edge_length[result.size++] = node_distance[v][w];
			for (int i = 0; i < tree_size; ++i)
				if (v != i && i == dsu_find(i))
				{
					node_distance[v][i] = node_distance[i][v] = (node_distance[v][i] + node_distance[w][i]) * 0.5;
					heap_push(make_edge(v, i));
				}
		}
		for (int i = 0; i < tree_size; ++i)
			if (dsu_find(i) == i)
				++result.root_size;
		result.root = (int *)malloc(sizeof(int) * result.root_size);
		for (int i = 0, j = 0; i < tree_size; ++i)
			if (dsu_find(i) == i)
				result.root[j++] = x[i];
		free(dsu_father);
		free(x);
	}
	{
		/* 调整子树顺序 */
		int *u = (int *)malloc(sizeof(int) * result.size), v = 0;
		for (hash_node *i = hash_table_begin(); i != NULL; i = hash_table_next(i))
			block_list_to_double(i->node->distance, node_distance[v++]);
		for (int i = 0; i < tree_size; ++i)
			u[i] = i;
		for (int i = 0; i < result.root_size; ++i)
			rearrangement_subtree(&result, u, result.root[i]);
		for (int i = 0; i < tree_size; ++i)
			free(node_distance[i]);
		free(node_distance);
		free(u);
	}
	return result;
}
#undef tree_size
