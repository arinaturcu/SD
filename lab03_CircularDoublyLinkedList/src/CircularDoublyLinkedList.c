#include <stdio.h>
#include <stdlib.h>

#include "CircularDoublyLinkedList.h"

/*
 * Functie care trebuie apelata dupa alocarea unei liste, pentru a o initializa.
 * (Setare valori initiale pentru campurile specifice structurii LinkedList).
 */
void init_list(struct CircularDoublyLinkedList *list) {
    list->head = NULL;
    list->size = 0;
}

/*
 * Functia intoarce un pointer la nodul de pe pozitia n din lista.
 * Pozitiile din lista sunt indexate incepand cu 0 (i.e. primul nod din lista se afla pe pozitia n=0).
 * Daca n >= nr_noduri, atunci se intoarce nodul de pe pozitia rezultata daca am "cicla" (posibil de mai multe ori) pe
 * lista si am trece de la ultimul nod, inapoi la primul si am continua de acolo. Cum putem afla pozitia dorita fara sa
 * simulam intreaga parcurgere?
 * Daca n < 0, eroare.
 */
struct Node* get_nth_node(struct CircularDoublyLinkedList *list, int n) {
    struct Node *curr;
    int p = 0;

    if (n < 0 || list == NULL) {
        return NULL;
    }

    curr = list->head;

    if (n > ((list->size) - 1)) {
        n = n % (list->size);
    }

    while (p < n) {
        curr = curr->next;
        p++;
    }

    return curr;
}

/*
 * Pe baza datelor trimise prin pointerul new_data, se creeaza un nou nod care e adaugat pe pozitia n a listei
 * reprezentata de pointerul list. Pozitiile din lista sunt indexate incepand cu 0 (i.e. primul nod din lista se afla
 * pe pozitia n=0).
 * Cand indexam pozitiile nu "ciclam" pe lista circulara ca la get, ci consideram nodurile in ordinea de la head la
 * ultimul (adica acel nod care pointeaza la head ca nod urmator in lista). Daca n >= nr_noduri, atunci adaugam nodul
 * nou la finalul listei. Daca n < 0, eroare.
 */
void add_nth_node(struct CircularDoublyLinkedList *list, int n, void *new_data) {
    struct Node *curr, *new;
    int p = 0;

    if (n < 0 || list == NULL) {
        return;
    }

    curr = list->head;

    new = (struct Node*)malloc(sizeof(struct Node));
    new->data = new_data;
    new->prev = NULL;
    new->next = NULL;

    if (list->size == 0) {
        list->head = new;
        new->next = new;
        new->prev = new;

        list->size++;

        return;
    }

    /* add last (or first)*/

    if (n >= (list->size) || n == 0) {
        while (p < (list->size) - 1) {
            curr = curr->next;
            p++;
        }

        curr->next = new;
        new->prev = curr;
        list->head->prev = new;
        new->next = list->head;

        if (n == 0) {
            list->head = new;
        }

        list->size++;

        return;
    }

    while (p < n - 1) {
        curr = curr->next;
        p++;
    }

    new->next = curr->next;
    new->next->prev = new;
    curr->next = new;
    new->prev = curr;

    list->size++;

}

/*
 * Elimina nodul de pe pozitia n din lista al carei pointer este trimis ca parametru.
 * Pozitiile din lista se indexeaza de la 0 (i.e. primul nod din lista se afla pe pozitia n=0).
 * Functia intoarce un pointer spre acest nod proaspat eliminat din lista. Daca n >= nr_noduri - 1, se elimina nodul de
 * la finalul listei. Daca n < 0, eroare.
 * Este responsabilitatea apelantului sa elibereze memoria acestui nod.
 */
struct Node* remove_nth_node(struct CircularDoublyLinkedList *list, int n) {
    struct Node *old;
    int p = 0;

    if (n < 0 || list == NULL || list->size == 0) {
        return NULL;
    }

    if (list->size == 1) {
        old = list->head;
        list->head = NULL;
        list->size--;

        return old;
    }

    /* remove last */
    if (n >= list->size - 1) {
        old = list->head->prev;
        list->head->prev = old->prev;
        old->prev->next = list->head;

        list->size--;

        return old;
    }

    old = list->head;

    while (p < n) {
        old = old->next;
        p++;
    }

    old->next->prev = old->prev;
    old->prev->next = old->next;

    if (n == 0) {
        list->head = old->next;
    }

    list->size--;

    return old;
}

/*
 * Functia intoarce numarul de noduri din lista al carei pointer este trimis ca parametru.
 */
int get_size(struct CircularDoublyLinkedList *list) {

    if (list == NULL) {
        return -1;
    }

    return list->size;
}

/*
 * Procedura elibereaza memoria folosita de toate nodurile din lista, iar la sfarsit, elibereaza memoria folosita
 * de structura lista.
 */
void free_list(struct CircularDoublyLinkedList **pp_list) {
    struct Node *curr, *pre_curr;

    pre_curr = (*pp_list)->head;
    curr = pre_curr->next;

    while ((*pp_list)->size > 1) {
        free(pre_curr);

        pre_curr = curr;
        curr = curr->next;

        (*pp_list)->size--;
    }

    free(pre_curr);
    (*pp_list)->size = 0;
    free(*pp_list);
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM ca stocheaza int-uri.
 * Functia afiseaza toate valorile int stocate in nodurile din lista separate printr-un spatiu, incepand de la primul
 * nod din lista.
 */
void print_int_list(struct CircularDoublyLinkedList *list) {
    struct Node *curr;
    int p = 0;

    if (list->size == 0) {
        printf("Lista goala.\n");
        return;
    }

    curr = list->head;

    while (p < (list->size - 1)) {
        printf("%d ", *((int *)curr->data));
        curr = curr->next;
        p++;
    }

    printf("%d ", *((int *)curr->data));

    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM ca stocheaza string-uri.
 * Functia afiseaza toate string-urile stocate in nodurile din lista separate printr-un spatiu, incepand de la primul
 * nod din lista.
 */
void print_string_list(struct CircularDoublyLinkedList *list) {
    struct Node *curr;
    int p = 0;

    curr = list->head;

    while (p < (list->size - 1)) {
        printf("%s ", ((char *)curr->data));
        curr = curr->next;
        p++;
    }

    printf("%s ", ((char *)curr->data));

    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM ca stocheaza int-uri.
 * Functia afiseaza o singura data toate valorile int stocate in nodurile din lista, separate printr-un spatiu, incepand
 * de la nodul dat ca parametru si continuand la stanga in lista dublu inlantuita circulara, pana cand sunt afisate
 * valorile tuturor nodurilor.
 */
void print_ints_left_circular(struct Node *start) {
    struct Node *curr;
    int p = 0;

    printf("%d ", *((int *)start->data));

    curr = start->prev;

    while (curr->prev != start) {
        printf("%d ", *((int *)curr->data));
        curr = curr->prev;
        p++;
    }

    printf("%d ", *((int *)curr->data));

    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM ca stocheaza int-uri.
 * Functia afiseaza o singura data toate valorile int stocate in nodurile din lista, separate printr-un spatiu, incepand
 * de la nodul dat ca parametru si continuand la dreapta in lista dublu inlantuita circulara, pana cand sunt afisate
 * valorile tuturor nodurilor.
 */
void print_ints_right_circular(struct Node *start) {
    struct Node *curr;
    int p = 0;

    printf("%d ", *((int *)start->data));

    curr = start->next;

    while (curr->next != start) {
        printf("%d ", *((int *)curr->data));
        curr = curr->next;
        p++;
    }

    printf("%d ", *((int *)curr->data));

    printf("\n");
}
