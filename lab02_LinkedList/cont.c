#include <stdio.h>
#include <stdlib.h>

struct Node {
    void *data; /* Pentru ca datele stocate sa poata avea orice tip, folosim un pointer la void. */
    struct Node *next;
};

struct LinkedList {
    struct Node *head;
    int size; 
};

void init_list(struct LinkedList *list) {
    list->head = NULL;
    list->size = 0;
}

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

struct LinkedList *merge(struct LinkedList *list1, struct LinkedList *list2) {
	struct LinkedList *merged;
	struct Node *curr, *l1, *l2, *aux1, *aux2;

	merged = malloc(sizeof(struct LinkedList));

	merged->head = list1->head;
	curr = merged->head;
	l2 = list2->head;
	l1 = list1->head->next;

	while (l1 != NULL) {

		aux1 = l1->next;
		aux2 = l2->next;

		curr->next = l2;
		curr = curr->next;

		curr->next = l1;
		curr = curr->next;

		l1 = aux1;
		l2 = aux2;
	}

	curr->next = l2;
	curr->next->next = NULL;

	return merged;
}

int main() {
	struct LinkedList *list1, *list2, *merged;

	int numbers[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    list1 = malloc(sizeof(struct LinkedList));
    list2 = malloc(sizeof(struct LinkedList));
    init_list(list1);
    init_list(list2);

    add_nth_node(list1, 0, &numbers[1]);
    add_nth_node(list1, 1, &numbers[2]);
    add_nth_node(list1, 2, &numbers[3]);

    add_nth_node(list2, 0, &numbers[4]);
    add_nth_node(list2, 1, &numbers[5]);
    add_nth_node(list2, 2, &numbers[6]);

    print_int_linkedlist(list1);
    print_int_linkedlist(list2);

    merged = merge(list1, list2);

    print_int_linkedlist(merged);
}