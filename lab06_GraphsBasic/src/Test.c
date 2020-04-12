#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ListGraph.h"
#include "MatrixGraph.h"
#include "Queue.h"
#include "Stack.h"

#define MAX_NODES 10

void print_matrix_graph(MatrixGraph *g) {
    int i, j;
    for (i = 0; i < g->nodes; ++i) {
        printf("%d: ", i);
        for (j = 0; j < g->nodes; ++j) {
            if (g->matrix[i][j] == 1) {
                printf("%d ", j);
            }
        }
        printf("\n");
    }
}

void print_list_graph(ListGraph *g) {
    int i;

    for (i = 0; i < g->nodes; ++i) {
        printf("%d: ", i);
        print_int_linkedlist(g->neighbors[i]);
    }
}

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

void dfs_matrix_graph(MatrixGraph *mg, int node, int *visited, int *t_desc, int *t_fin, int *time) {
    visited[node] = 1;
    t_desc[node] = *time;
    (*time)++;

    for (int i = 0; i < mg->nodes; ++i) {
        if (mg->matrix[node][i] == 1 && visited[i] == 0) {
            dfs_matrix_graph(mg, i, visited, t_desc, t_fin, time);
        }
    }

    t_fin[node] = *time;
    (*time)++; 
}

void bfs_list_graph(ListGraph *lg, int node, int *visited, int *parents) {
    int d[MAX_NODES]; /* distanta de la sursa la fiecare nod */
    Queue *q;
    int i, node2;
    Node *v_node;

    q = malloc(sizeof(Queue));
    init_q(q);

    /* initializare */
    for (i = 0; i < lg->nodes; ++i) {
        visited[i] = 0;
        d[i] = 0x7fffffff;
    }

    visited[node] = 1;
    d[node] = 0;
    enqueue(q, &node);

    while (is_empty_q(q) == 0) {
        node2 = *(int *)front(q);
        dequeue(q);

        v_node = lg->neighbors[node2]->head;
        while (v_node != NULL) {
            
            if ( visited[*(int *)v_node->data] == 0 ) {
                visited[*(int *)v_node->data] = 1;
                parents[*(int *)v_node->data] = node2;
                d[*(int *)v_node->data] = d[node2] + 1;
                enqueue(q, v_node->data);
            }
            v_node = v_node->next;
        }
    }
    purge_q(q);
    free(q);
}

void bfs_matrix_graph(MatrixGraph *mg, int node, int *visited, int *parents) {
    int d[MAX_NODES]; /* distanta de la sursa la fiecare nod */
    Queue *q;
    int i, k, node2;
    int vec[MAX_NODES], n = 0; /* pentru ca atunci cand modific node2 sa nu se modifice coada */

    q = malloc(sizeof(Queue));
    init_q(q);

    /* initializare */
    for (i = 0; i < mg->nodes; ++i) {
        visited[i] = 0;
        d[i] = 0x7fffffff;
    }

    visited[node] = 1;
    d[node] = 0;
    vec[n] = node;
    enqueue(q, &vec[n]);

    while (is_empty_q(q) == 0) {
        node2 = *(int *)front(q);
        dequeue(q);

        for (k = 0; k < mg->nodes; ++k) {
            
            if ( visited[k] == 0 && mg->matrix[node2][k] == 1) {
                visited[k] = 1;
                parents[k] = node2;
                d[k] = d[node2] + 1;
                n++;
                vec[n] = k;
                enqueue(q, &vec[n]);
            }
        }
    }
    purge_q(q);
    free(q);
}

void floyd_warshall(MatrixGraph *mg) {
    /* initializare */
    for (int i = 0; i < mg->nodes; ++i) {
        for (int j = 0; j < mg->nodes; ++j) {
            if (mg->matrix[i][j] == 0 && i != j) {
                mg->matrix[i][j] = mg->nodes;
            }
        }
    }

    for (int k = 0; k < mg->nodes; ++k) {
        for (int i = 0; i < mg->nodes; ++i) {
            for (int j = 0; j < mg->nodes; ++j) {
                if (mg->matrix[i][j] > mg->matrix[i][k] + mg->matrix[k][j]) {
                    mg->matrix[i][j] = mg->matrix[i][k] + mg->matrix[k][j];
                }
            }
        }
    }

    /* finalizare */
    for (int i = 0; i < mg->nodes; ++i) {
        for (int j = 0; j < mg->nodes; ++j) {
            if (mg->matrix[i][j] == mg->nodes) {
                mg->matrix[i][j] = 0;
            }
        }
    }
}

/* Afiseaza timpii de descoperire si de finalizare ai fiecarui nod din graf. */
void print_times(int* t_desc, int* t_fin, int nodes)
{
    int i;

    for (i = 0; i < nodes; ++i)
    {
        printf("%d: %d/%d\n", i, t_desc[i], t_fin[i]);
    }
    printf("\n");
}

/* Afiseaza parintii nodurilor din graf. */
void print_parents(int* parents, int nodes)
{
    int i;

    for (i = 0; i < nodes; ++i)
    {
        printf("%d: %d\n", i, parents[i]);
    }
    printf("\n");
}

/* Afiseaza distantele dintre oricare doua noduri din graf */
void print_distances(MatrixGraph* mg)
{
    int i, j;

    for (i = 0; i < mg->nodes; ++i)
    {
        printf("%d:", i);
        for (j = 0; j < mg->nodes; ++j)
        {
            printf(" %d", mg->matrix[i][j]);
        }
        printf("\n");
    }
}

int main(void) {
    int nodes, edges;
    int x[MAX_NODES], y[MAX_NODES];
    int visited[MAX_NODES], t_desc[MAX_NODES], t_fin[MAX_NODES];
    int parents[MAX_NODES];
    int time;
    ListGraph *lg = malloc(sizeof(ListGraph));
    MatrixGraph *mg = malloc(sizeof(MatrixGraph));

    scanf("%d %d", &nodes, &edges);

    init_list_graph(lg, nodes);
    init_matrix_graph(mg, nodes);

    for (int i = 0; i < edges; ++i) {
        scanf("%d %d", &x[i], &y[i]);
        add_edge_matrix_graph(mg, x[i], y[i]);
        add_edge_list_graph(lg, x[i], &y[i]);
    }

    printf("====== Graf modelat cu matrice de adiacenta ======\n");
    print_matrix_graph(mg);

    printf("====== Graf modelat cu liste de adiacenta ======\n");
    print_list_graph(lg);

    time = 0;
    memset(visited, 0, sizeof(visited));
    dfs_list_graph(lg, 0, visited, t_desc, t_fin, &time);
    printf("====== Timpi de descoperire si finalizare - graf modelat cu liste ======\n");
    print_times(t_desc, t_fin, lg->nodes);

    time = 0;
    memset(visited, 0, sizeof(visited));
    dfs_matrix_graph(mg, 0, visited, t_desc, t_fin, &time);
    printf("====== Timpi de descoperire si finalizare - graf modelat cu matrice ======\n");
    print_times(t_desc, t_fin, mg->nodes);

    printf("====== Parintii nodurilor - graf modelat cu matrice ======\n");
    memset(visited, 0, sizeof(visited));
    memset(parents, 0xff, sizeof(parents));  /* parents[i] = -1; i = 0:(nodes - 1) */
    bfs_list_graph(lg, 0, visited, parents);
    print_parents(parents, lg->nodes);

    printf("====== Parintii nodurilor - graf modelat cu liste ======\n");
    memset(visited, 0, sizeof(visited));
    memset(parents, 0xff, sizeof(parents));  /* parents[i] = -1; i = 0:(nodes - 1) */
    bfs_matrix_graph(mg, 0, visited, parents);
    print_parents(parents, mg->nodes);

    printf("====== Distantele dintre oricare doua noduri - graf modelat cu matrice ======\n");
    floyd_warshall(mg);
    print_distances(mg);

    clear_list_graph(lg);
    clear_matrix_graph(mg);
    free(lg);
    free(mg);
    return 0;
}