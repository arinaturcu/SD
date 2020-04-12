#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ListGraph.h"
#include "Queue.h"

#define MAX_NODES 100

/*
void dfs_list_graph(ListGraph *lg, int node, int *visited, int *t_desc, int *t_fin, int *time) {
    visited[node] = 1;
    t_desc[node] = *time;
    (*time)++;

    Node *next_node = lg->neighbors[node]->head;
    while (next_node != NULL) {
        if (visited[*((int *)next_node->data)] == 0) {
            dfs_list_graph(lg, *((int *)next_node->data), visited, t_desc, t_fin, time);
        }
        next_node = next_node->next;
    }

    t_fin[node] = *time;
    (*time)++;
}
*/

void dfs_connected_comps(ListGraph *lg, int *node, int *visited) {
    visited[*node] = 1;
    
    Node *next_node = lg->neighbors[*node]->head;
    
    while (next_node != NULL) {
        if (visited[*((int *)next_node->data)] == 0) {
            dfs_connected_comps(lg, (int *)next_node->data, visited);
        }
        next_node = next_node->next;
    }
}

void connected_components(ListGraph *lg, int *nodes_index) {
    int visited[MAX_NODES] = {0};
    int i;
    int components = 0;

    for (i = 0; i < MAX_NODES; ++i) {
        if (nodes_index[i] != 0 && visited[i] == 0) {
            components++;
            dfs_connected_comps(lg, &nodes_index[i], visited);
        }
    }
    printf("Componente conexe: %d\n", components);
}

void dfs_topo_sort(ListGraph *lg, int *node, int *visited, LinkedList *result) {
    /* TODO */
}

void topo_sort(ListGraph *lg, int *nodes_index) {
    /* TODO */
}

void min_path(ListGraph *lg, int *nodes_index) {
    /* TODO */
}

int check_bipartite(ListGraph *lg, int *nodes_index, int *color) {
    /* TODO */
}

int main() {
    int nodes, edges;
    int color[MAX_NODES];
    int nodes_index[MAX_NODES] = {0};
    int x[MAX_NODES], y[MAX_NODES];
    ListGraph *lg = malloc(sizeof(ListGraph));

    scanf("%d %d", &nodes, &edges);
    init_list_graph(lg, nodes);
    for (int i = 0; i < nodes; ++i) {
        nodes_index[i] = i;
    }

    for (int i = 0; i < edges; ++i) {
        scanf("%d %d", &x[i], &y[i]);
        add_edge_list_graph(lg, x[i], &y[i]);
    }

    /* Ex 1 */
    connected_components(lg, nodes_index);

    /* Ex 2 */
    topo_sort(lg, nodes_index);

    /* Ex 3 */
    min_path(lg, nodes_index);

    /* Ex 4 */
    if (check_bipartite(lg, nodes_index, color)) {
        for (int i = 0; i < lg->nodes; ++i) {
            if (color[i] == 1) {
                printf("%d ", i);
            }
        } 
        printf("\n");
        for (int i = 0; i < lg->nodes; ++i) {
            if (color[i] == 0) {
                printf("%d ", i);
            }
        } 
        printf("\n");
    } else {
        printf("The graph is not bipartite\n");
    }

    clear_list_graph(lg);
    free(lg);
    return 0;
}