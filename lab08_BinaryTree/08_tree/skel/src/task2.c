/**
 * SD, 2020
 * 
 * Lab #8, Binary Tree
 * 
 * Task #2 - LCA
 * Accepted complexity is O(N) per query, but you can try to do better!
 * https://infoarena.ro/problema/lca
 */

#include <stdio.h>
#include <stdlib.h>

#include "binary_tree.h"

void read_tree(b_tree_t *b_tree)
{
	int i, data, N;

	scanf("%d\n", &N);

	for (i = 0; i < N; ++i) {
		scanf("%d ", &data);
		b_tree_insert(b_tree, data);
	}
}

b_node_t *lca(b_node_t *node, int node1, int node2)
{
	if (node == NULL) {
		return NULL;
	}

	if (*node->data == node1 || *node->data == node2) {
		return node;
	}

	b_node_t *l_left = lca(node->left, node1, node2);
	b_node_t *l_right = lca(node->right, node1, node2);

	if (l_left && l_right) return node;

	// daca unul dintre left si right este NULL
	if (l_left) return l_left;
	if (l_right) return l_right;

	return NULL;
}

int find_LCA(b_tree_t *b_tree, int node1, int node2)
{	
	b_node_t *node = lca(b_tree->root, node1, node2);
	
	return *node->data;
}

void do_queries(b_tree_t *b_tree)
{
	int i, node1, node2, num_queries;

	scanf("%d\n", &num_queries);

	for (i = 0; i != num_queries; ++i) {
		scanf("%d %d\n", &node1, &node2);
		printf("LCA of nodes %d and %d is %d\n", node1, node2,
			find_LCA(b_tree, node1, node2));
	}
}

int main(void)
{
	b_tree_t *binary_tree;

	binary_tree = b_tree_create();

	read_tree(binary_tree);
	do_queries(binary_tree);

	b_tree_free(binary_tree);

	return 0;
}