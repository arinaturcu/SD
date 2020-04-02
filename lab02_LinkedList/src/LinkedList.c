#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"

/*
 * Functie care trebuie apelata dupa alocarea unei liste simplu inlantuite, pentru a o initializa.
 * (Setare valori initiale pentru campurile specifice structurii LinkedList).
 */
void init_list(struct LinkedList *list) {
    list->head = NULL;
    list->size = 0;
}

/*
 * Pe baza datelor trimise prin pointerul new_data, se creeaza un nou nod care e adaugat pe pozitia n a listei
 * reprezentata de pointerul list. Pozitiile din lista sunt indexate incepand cu 0 (i.e. primul nod din lista se afla
 * pe pozitia n=0). Daca n >= nr_noduri, noul nod se adauga la finalul listei. Daca n < 0, eroare.
 */
void add_nth_node(struct LinkedList *list, int n, void *new_data) {
    int size = list->size;
    struct Node *curr, *new;
    curr = list->head;

    new = (struct Node*) malloc(sizeof(struct Node));
    new->data = new_data;
    new->next = NULL;

    if (n < 0) {
    	printf("Eroare n < 0.\n");
    	return;
    }

    if (size == 0) {
    	list->head = new;
    	list->size++;
    	return;
    }

    if (n >= size) {
    	int p = 0;

    	while (p < size - 1) {
    		curr = curr->next;
    		p++;
    	}

    	curr->next = new;
    	list->size++;
    	return;
    }

    if (n == 0) {
    	new->next = list->head;
    	list->head = new;
    	list->size++;
    	return;
    }

    if (n < size) {
    	int p = 0;

    	while (p < n - 1) {
    		curr = curr->next;
    		p++;
    	}

    	new->next = curr->next;
    	curr->next = new;
    	list->size++;
    }
}

/*
 * Elimina nodul de pe pozitia n din lista al carei pointer este trimis ca parametru.
 * Pozitiile din lista se indexeaza de la 0 (i.e. primul nod din lista se afla pe pozitia n=0). Daca n >= nr_noduri - 1,
 * se elimina nodul de la finalul listei. Daca n < 0, eroare.
 * Functia intoarce un pointer spre acest nod proaspat eliminat din lista.
 * Este responsabilitatea apelantului sa elibereze memoria acestui nod.
 */
struct Node* remove_nth_node(struct LinkedList *list, int n) {
    int size = list->size;
    struct Node *curr, *old;
    int p = 0;

    curr = list->head;

    if (n < 0) {
    	printf("Eroare n < 0.\n");
    	return NULL;
    }

    if (size == 0) {
    	return NULL;
    }

    if (size == 1) {
    	old = curr;
    	list->head = NULL;
    	list->size--;

    	return old;
    }

    if (n >= size - 1) {
    	while (p < size - 2) {
    		curr = curr->next;
    		p++;
    	}

    	old = curr->next;
    	curr->next = NULL;
    	list->size--;
    	return old;
    }

    if (n == 0) {
    	old = list->head;
    	list->head = old->next;
    	list->size--;
    	return old;
    }

    if (n < size) {
    	while (p < n - 1) {
    		curr = curr->next;
    		p++;
    	}

    	old = curr->next;
    	curr->next = curr->next->next;
    	list->size--;
    	return old;
    }

    return NULL;
}

/*
 * Functia intoarce numarul de noduri din lista al carei pointer este trimis ca parametru.
 */
int get_size(struct LinkedList *list) {
    int size = 0;
    struct Node *curr;

    curr = list->head;

    while (curr->next != NULL) {
    	curr = curr->next;
    	size++;
    }

    return size;
}

/*
 * Procedura elibereaza memoria folosita de toate nodurile din lista, iar la sfarsit, elibereaza memoria folosita
 * de structura lista si actualizeaza la NULL valoarea pointerului la care pointeaza argumentul (argumentul este un
 * pointer la un pointer).
 */
void free_list(struct LinkedList **pp_list) {
    struct Node *curr;
    int size = (*pp_list)->size;
    int p = 0;

    while(size > 0) {

    	curr = (*pp_list)->head;

    	while (p < size - 1) {
    		curr = curr->next;
    		p++;
    	}
    	free(curr);
    	size--;
    }

    free(*pp_list);
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM ca stocheaza int-uri.
 * Functia afiseaza toate valorile int stocate in nodurile din lista inlantuita separate printr-un spatiu.
 */
void print_int_linkedlist(struct LinkedList *list) {
    struct Node *curr;

    curr = list->head;

    while (curr->next != NULL) {
    	printf("%d ", *((int *)curr->data));
    	curr = curr->next;
    }

   	printf("%d ", *((int *)curr->data));

    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM ca stocheaza string-uri.
 * Functia afiseaza toate string-urile stocate in nodurile din lista inlantuita, separate printr-un spatiu.
 */
void print_string_linkedlist(struct LinkedList *list) {
    struct Node *curr;

    curr = list->head;

    while (curr->next != NULL) {
    	printf("%s ", ((char *)curr->data));
    	curr = curr->next;
    }

   	printf("%s ", ((char *)curr->data));

    printf("\n");
}
