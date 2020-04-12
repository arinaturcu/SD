#include <stdio.h>
#include <stdlib.h>

#include "ListGraph.h"
#include "MatrixGraph.h"
#include "LinkedList.h"
#include "Queue.h"
#include "Stack.h"

#define MAX_NODES 30

void print_matrix_graph(MatrixGraph *g) {
    int i, j;
    for (i = 0; i < g->nodes; ++i) {
        for (j = 0; j < g->nodes; ++j) {
            printf("%d ", g->matrix[i][j]);
        }
        printf("\n");
    }
}

void print_list_graph(ListGraph *g) {
    int i;

    for (i = 0; i < g->nodes; ++i) {
        printf("nodul %d: ", i);
        print_int_linkedlist(g->neighbors[i]);
    }
}

void dfs_list_graph(ListGraph *lg, int node, int *visited, int *t_desc, int *t_fin, int *time) {
    int i, top_node, frst_ngbr[MAX_NODES], n = 0;
    Node *curr;
    Stack *s;
    
    /* initializare */
    for (i = 0; i < lg->nodes; ++i) {
        visited[i] = 0;
        t_desc[i] = 0;
        t_fin[i] = 0;
    }

    s = malloc(sizeof(Stack));
    init_stack(s);

    /* vizitez node */
    t_desc[node] = *time;
    visited[node] = 1;
    (*time)++;

    push_stack(s, &node);

    while (is_empty_stack(s) == 0) {
        top_node = *(int *)peek_stack(s);
        curr = NULL;

        /* afla primul vecin nevizitat al lui top_node */
        if (lg->neighbors[top_node]->size > 0) {
            curr = lg->neighbors[top_node]->head;

            while (curr != NULL && visited[*(int *)curr->data] != 0) {
                curr = curr->next;
            }
        }
        
        /* daca exita vecin nevizitat */
        if (curr != NULL) {

            frst_ngbr[n] = *(int *)curr->data;
            
            /* vizitez frst_ngbr */
            t_desc[frst_ngbr[n]] = *time;
            visited[frst_ngbr[n]] = 1;
            (*time)++;

            push_stack(s, &frst_ngbr[n]);
            n++;

        } else {

            t_fin[top_node] = *time;
            (*time)++;
            pop_stack(s);

        }
    }
    purge_stack(s);
    free(s);
}

void dfs_matrix_graph(MatrixGraph *mg, int node, int *color, int *t_desc, int *t_fin, int *parent) {
    /* alb = 0;
     * gri = 1;
     * negru = 9;
     */
    int i, contor_tmp, top_node, frst_ngbr[MAX_NODES], n = 0, curr;
    Stack *s;
    
    /* initializare */
    for (i = 0; i < mg->nodes; ++i) {
        color[i] = 0;
        parent[i] = 0x7fffffff;
        t_desc[i] = 0;
        t_fin[i] = 0;
    }
    contor_tmp = 0;

    s = malloc(sizeof(Stack));
    init_stack(s);

    /* vizitez node */
    contor_tmp++;
    t_desc[node] = contor_tmp;
    color[node] = 1;
    printf("%d ", node);

    push_stack(s, &node);

    while (is_empty_stack(s) == 0) {
        top_node = *(int *)peek_stack(s);
        curr = 0x7fffffff;

        /* afla primul vecin nevizitat al lui top_node */
        for (i = 0; i < mg->nodes; ++i) {
            if (mg->matrix[top_node][i] == 1 && color[i] == 0) {
                curr = i;
                break;
            }
        }
        
        /* daca exita vecin nevizitat */
        if (curr != 0x7fffffff) {
            frst_ngbr[n] = curr;
            parent[frst_ngbr[n]] = top_node;
            
            /* vizitez frst_ngbr */
            contor_tmp++;
            t_desc[frst_ngbr[n]] = contor_tmp;
            color[frst_ngbr[n]] = 1;
            printf("%d ", frst_ngbr[n]);

            push_stack(s, &frst_ngbr[n]);
            n++;

        } else {

            contor_tmp++;
            t_fin[top_node] = contor_tmp;
            color[top_node] = 9;
            pop_stack(s);

        }
    }
    printf("\n");
    purge_stack(s);
    free(s);
}

void bfs_list_graph(ListGraph *lg, int node, int *color, int *parent) {
    /* alb = 0;
     * gri = 1;
     * negru = 9; 
     */
    int d[MAX_NODES]; /* distanta de la sursa la fiecare nod */
    Queue *q;
    int i, node2;
    Node *v_node;

    q = malloc(sizeof(Queue));
    init_q(q);

    /* initializare */
    for (i = 0; i < lg->nodes; ++i) {
        color[i] = 0;
        d[i] = 0x7fffffff;
        parent[i] = 0x7fffffff;
    }

    color[node] = 1;
    d[node] = 0;
    enqueue(q, &node);
    printf("%d ", node);

    while (is_empty_q(q) == 0) {
        node2 = *(int *)front(q);
        dequeue(q);

        v_node = lg->neighbors[node2]->head;
        while (v_node != NULL) {
            
            if ( color[*(int *)v_node->data] == 0 ) {
                printf("%d ", *(int *)v_node->data);

                color[*(int *)v_node->data] = 1;
                parent[*(int *)v_node->data] = node2;
                d[*(int *)v_node->data] = d[node2] + 1;
                enqueue(q, v_node->data);
            }
            v_node = v_node->next;
        }
        color[node2] = 9;
    }
    printf("\n");
    purge_q(q);
    free(q);
}

void bfs_matrix_graph(MatrixGraph *mg, int node, int *color, int *parent) {
     /* alb = 0;
     * gri = 1;
     * negru = 9; 
     */
    int d[MAX_NODES]; /* distanta de la sursa la fiecare nod */
    Queue *q;
    int i, k, node2;
    int vec[MAX_NODES], n = 0; /* pentru ca atunci cand modific node2 sa nu se modifice coada */

    q = malloc(sizeof(Queue));
    init_q(q);

    /* initializare */
    for (i = 0; i < mg->nodes; ++i) {
        color[i] = 0;
        d[i] = 0x7fffffff;
        parent[i] = 0x7fffffff;
    }

    color[node] = 1;
    d[node] = 0;
    vec[n] = node;
    enqueue(q, &vec[n]);
    printf("%d ", node);

    while (is_empty_q(q) == 0) {
        node2 = *(int *)front(q);
        dequeue(q);

        for (k = 0; k < mg->nodes; ++k) {
            
            if ( color[k] == 0 && mg->matrix[node2][k] == 1) {
                printf("%d ", k);

                color[k] = 1;
                parent[k] = node2;
                d[k] = d[node2] + 1;
                n++;
                vec[n] = k;
                enqueue(q, &vec[n]);
            }
        }
        color[node2] = 9;
    }
    printf("\n");
    purge_q(q);
    free(q);
}

void floyd_warshall(MatrixGraph *lg) {
    /* TODO BONUS */
}

int main() {
    int nodes, edges;
    int color[MAX_NODES], t_dest[MAX_NODES], t_fin[MAX_NODES], parent[MAX_NODES];
    ListGraph *lg = malloc(sizeof(ListGraph));
    MatrixGraph *mg = malloc(sizeof(MatrixGraph));

    nodes = 9; edges = 12;

    /* ca sa il fac graf neorientat am adaugat o latura in ambele sensuri */
    int x[MAX_NODES] = {0, 0, 0, 1, 1, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 8};
    int y[MAX_NODES] = {1, 2, 3, 0, 4, 5, 0, 3, 6, 0, 6, 7, 1, 5, 8, 1, 4, 6, 2, 3, 5, 3, 4};

    init_list_graph(lg, nodes);
    init_matrix_graph(mg, nodes);

    for (int i = 0; i < edges*2; ++i) {
        add_edge_matrix_graph(mg, x[i], y[i]);
        add_edge_list_graph(lg, x[i], &y[i]);
    }

    printf("\nMatrice de adiacenta:\n\n");
    print_matrix_graph(mg);
    printf("\nListe de adiacenta:\n\n");
    print_list_graph(lg);

    /* PENTRU TESTAREA FUNCTIILOR DE REMOVE EDGE
    
    remove_edge_list_graph(lg, x[2], y[2]);
    remove_edge_matrix_graph(mg, x[2], y[2]);
    
    printf("\nMatrice de adiacenta:\n\n");
    print_matrix_graph(mg);
    printf("\nListe de adiacenta:\n\n");
    print_list_graph(lg); 
    */

    printf ("\nParcurgere BFS pe liste:\n");
    bfs_list_graph(lg, 8, color, parent);
    printf ("\nParcurgere BFS pe matrice:\n");
    bfs_matrix_graph(mg, 8, color, parent);

    printf ("\nParcurgere DFS pe liste:\n");
    dfs_list_graph(lg, 8, color, t_dest, t_fin, parent);
    printf ("\nParcurgere DFS pe matrice:\n");
    dfs_matrix_graph(mg, 8, color, t_dest, t_fin, parent);

    clear_list_graph(lg);
    clear_matrix_graph(mg);
    free(lg);
    free(mg);
    return 0;
}