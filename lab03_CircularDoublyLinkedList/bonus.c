#include <stdio.h>
#include <stdlib.h>

struct Node {
    void *data; /* Pentru ca datele stocate sa poata avea orice tip, folosim un pointer la void. */
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

void add_nth_node(struct DoublyLinkedList *list, int n, void *new_data) {
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

void print_int_list(struct DoublyLinkedList *list) {
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

int get_pos (struct DoublyLinkedList *list, struct Node *n) {
	struct Node *curr;
	int pos = 0;
	curr = list->head;

	while (curr != n) {
		curr = curr->next;
		pos++;
	}

	return pos;
}

void move_first(struct DoublyLinkedList *list, struct Node *to_move) {

	int p;
	p = get_pos(list, to_move);

	if (p == 0) {
		return;
	}

	if (p == 1) {
		list->head->prev = to_move;
		list->head->next = to_move->next;
		to_move->next = list->head;
		to_move->prev = NULL;

		list->head = to_move;

		return;
	}

	if (p == list->size - 1) {
		to_move->next = list->head;
		list->head->prev = to_move;
		to_move->prev->next = NULL;
		to_move->prev = NULL;

		list->head = to_move;

		return;
	}

	if (p < list->size - 1) {
		to_move->next->prev = to_move->prev;
		to_move->prev->next = to_move->next;
		to_move->next = list->head;
		list->head->prev = to_move;
		to_move->prev = NULL;

		list->head = to_move;
	}
}

void reordered(struct DoublyLinkedList *list, int x) {
	struct Node *curr, *aux;
	int p = 0;

	curr = list->head;

	while (p < list->size) {

		if (*(int*)curr->data <= x) {

			aux = curr->next;
			move_first(list, curr);
			curr = aux;

		} else {
			curr = curr->next;
		}

		p++;
	}
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
	struct DoublyLinkedList *list;
	struct Node *curr;
	int numbers[] = {3, 6, 5, 4, 2};

    list = malloc(sizeof(struct DoublyLinkedList));
    init_list(list);

    add_nth_node(list, 0, &numbers[0]);
    add_nth_node(list, 1, &numbers[1]);
    add_nth_node(list, 2, &numbers[2]);
    add_nth_node(list, 3, &numbers[3]);
    add_nth_node(list, 4, &numbers[4]);

    print_int_list(list);

    reordered(list, 5);

    print_int_list(list);

    free_list(&list);

	return 0;
}
