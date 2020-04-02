/* Fiind date două liste dublu înlănţuite, A şi B, ale căror noduri stochează 
valori integer, construiţi o nouă listă dublu înlănţuită, C, pentru care 
fiecare nod i este suma nodurilor asociate din A şi B. Mai exact, nodul i
din C reţine suma dintre valoarea nodului i din A şi valoarea nodului i din B. 
Dacă una dintre listele primite este mai lungă decât cealaltă, se consideră 
că nodurile asociate lipsă din cealaltă listă conţin valoarea 0, adică 
se păstrează valorile din lista mai lungă */

/* are niste erori la valgrind */

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int *data; /* Pentru ca datele stocate sa poata avea orice tip, folosim un pointer la void. */
    struct Node *prev;
    struct Node *next;
};

struct DoublyLinkedList {
    struct Node *head;
    int size;    
};

void init_list(struct DoublyLinkedList *list) {
    list->head = NULL;
    list->size = 0;
}

void print_int_list(struct DoublyLinkedList *list) {
    struct Node *curr;
    int p = 0;

    if (list->size == 0) {
    	printf("Lista goala.\n");
    	return;
    }

    curr = list->head;

    while (p < (list->size - 1)) {
        printf("%d ", *curr->data);
        curr = curr->next;
        p++;
    }

    printf("%d ", *curr->data);

    printf("\n");
}

void add_nth_node(struct DoublyLinkedList *list, int n, int *new_data) {
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
        list->size++;

        return;
    }

    /* add last (or first)*/

    if (n >= (list->size)) {
        while (p < (list->size) - 1) {
            curr = curr->next;
            p++;
        }

        curr->next = new;
        new->prev = curr;

        list->size++;

        return;
    }

    if (n == 0) {
    	new->next = list->head;
    	list->head->prev = new;
    	list->head = new;
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

struct DoublyLinkedList* sum_them_lists(struct DoublyLinkedList *sum_list,
 		struct DoublyLinkedList *list1, struct DoublyLinkedList *list2) {
	
	int p = 0, *data;
	struct Node *curr1, *curr2, *new;

	if (list1->size == 0 && list2->size == 0) {
		return sum_list;
	}

	curr1 = list1->head;
	curr2 = list2->head;

	data = (int*)malloc(sizeof(int));

	while (p < list1->size && p < list2->size) {
		data = realloc(data, sizeof(int) * (p + 1));

		data[p] = *((int*)curr1->data) + *((int*)curr2->data);

		add_nth_node(sum_list, p, &data[p]);

		curr1 = curr1->next;
		curr2 = curr2->next;

		p++;
	}

	if (p < list1->size) {
		while(p < list1->size) {
			add_nth_node(sum_list, p, curr1->data);
			curr1 = curr1->next;
			p++;
		}

		return sum_list;
	}

	if (p < list2->size) {
		while(p < list2->size) {
			add_nth_node(sum_list, p, curr2->data);
			curr2 = curr2->next;
			p++;
		}

		return sum_list;
	}

	return sum_list;
}

void free_list(struct DoublyLinkedList **pp_list) {
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

int main() {
	struct DoublyLinkedList *list1, *list2, *sum_list;
	struct Node *curr;
	int numbers[] = {3, 7, 29, 4, 2, 4, 3};

    list1 = malloc(sizeof(struct DoublyLinkedList));
    list2 = malloc(sizeof(struct DoublyLinkedList));
    sum_list = malloc(sizeof(struct DoublyLinkedList));

    init_list(list1);
    init_list(list2);
    init_list(sum_list);

    add_nth_node(list1, 0, &numbers[0]);
    add_nth_node(list1, 1, &numbers[1]);
    add_nth_node(list1, 2, &numbers[2]);
    add_nth_node(list1, 3, &numbers[3]);

    add_nth_node(list2, 0, &numbers[4]);
    add_nth_node(list2, 1, &numbers[5]);
    add_nth_node(list2, 2, &numbers[6]);

    print_int_list(list1);
    print_int_list(list2);

    sum_list = sum_them_lists(sum_list, list1, list2);
    print_int_list(sum_list);

    free_list(&list1);
    free_list(&list2);
    free_list(&sum_list);

	return 0;
}