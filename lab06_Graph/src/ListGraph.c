#include <stdlib.h>
#include <stdio.h>

#include "ListGraph.h"
#include "LinkedList.h"

void init_list_graph(ListGraph *graph, int nodes) {
    int i;
    graph->nodes = nodes;
    graph->neighbors = malloc(sizeof(LinkedList *) * nodes);
    
    for (i = 0; i < nodes; ++i) {
        graph->neighbors[i] = malloc(sizeof(LinkedList));
        init_list(graph->neighbors[i]);
    }
}

void add_edge_list_graph(ListGraph *graph, int src, int *dest) {
    add_nth_node(graph->neighbors[src], 0x7fffffff, dest);
}

int has_edge_list_graph(ListGraph *graph, int src, int dest) {
    Node *curr_node;
    curr_node = graph->neighbors[src]->head;

    while (curr_node != NULL) {
        if (*(int *)curr_node->data == dest) {
            return 1;
        }
        curr_node = curr_node->next;
    }
    return 0;
}

LinkedList* get_neighbours_list_graph(ListGraph *graph, int node) {
    return graph->neighbors[node];
}

void remove_edge_list_graph(ListGraph *graph, int src, int dest) {
    Node *curr_node, *be_gone;
    int pos = 0;
    curr_node = graph->neighbors[src]->head;

    while (curr_node != NULL) {
        if (*(int *)curr_node->data == dest) {
            be_gone = remove_nth_node(graph->neighbors[src], pos);
            break;
        }
        curr_node = curr_node->next;
        pos++;
    }
    free(be_gone);
}

void clear_list_graph(ListGraph *graph) {
    int i;
    for (i = 0; i < graph->nodes; ++i) {
        free_list(&graph->neighbors[i]);
    }
    free(graph->neighbors);
}