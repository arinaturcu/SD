/* Copyright Arina Emanuela Turcu 313CA */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./commands.h"
#include "./playlist_utils.h"

struct Node* ADD_FIRST(struct DoublyLinkedList *list,
	char *song, struct Node *cursor, FILE *out) {
	struct Node *new, *dbl;

	new = malloc(sizeof(struct Node));

	new->track = get_info(new, song, out);
	new->next = NULL;
	new->prev = NULL;

	dbl = check_double(list, new);

	/* if the song already exist in the playlist deletes it*/
	if (dbl != NULL) {
		if (cursor == dbl) {
			if (cursor->next != NULL) {
				cursor = cursor->next;
			} else {
				if (cursor->prev != NULL) {
					cursor = cursor->prev;
				} else {
					cursor = new;
				}
			}
		}

		delete_node(list, dbl);
	}

	if (list->size == 0) {
		list->head = new;
		list->tail = new;
		list->size = 1;

		return new;
	}

	new->next = list->head;
	list->head->prev = new;
	list->head = new;
	list->size++;

	return cursor;
}

struct Node* ADD_LAST(struct DoublyLinkedList *list,
	char *song, struct Node *cursor, FILE *out){
	struct Node *new, *dbl;

	new = malloc(sizeof(struct Node));

	new->track = get_info(new, song, out);
	new->next = NULL;
	new->prev = NULL;

	dbl = check_double(list, new);

	/* if the song already exist in the playlist deletes it*/
	if (dbl != NULL) {
		if (cursor == dbl) {
			if (cursor->next != NULL) {
				cursor = cursor->next;
			} else {
				if (cursor->prev != NULL) {
					cursor = cursor->prev;
				} else {
					cursor = new;
				}
			}
		}

		delete_node(list, dbl);
	}

	if (list->size == 0) {
		list->head = new;
		list->tail = new;
		list->size = 1;

		return new;
	}

	new->prev = list->tail;
	list->tail->next = new;
	list->tail = new;
	list->size++;

	return cursor;
}

struct Node* ADD_AFTER(struct DoublyLinkedList *list,
	char *song, struct Node *cursor, FILE *out){
	struct Node *new, *dbl;

	if (cursor == NULL) {
		return NULL;
	}

	new = malloc(sizeof(struct Node));

	new->track = get_info(new, song, out);
	new->next = NULL;
	new->prev = NULL;

	/* if the cursor is pointed to the song to add or if the list is empty
	it does nothing */
	if (strcmp(new->track->title, cursor->track->title) == 0 || list->size == 0) {
		free(new->track->path_to_song);
		free(new->track);
		free(new);
		return cursor;
	}

	dbl = check_double(list, new);

	/* if the song already exist in the playlist it's deleted */
	if (dbl != NULL) {
		delete_node(list, dbl);
	}

	if (list->size == 1) {
		list->head->next = new;
		new->prev = list->head;
		list->size++;
		list->tail = new;

		return cursor;
	}

	/* if the cursor points to the head*/
	if (cursor == list->head) {
		new->next = cursor->next;
		cursor->next = new;
		new->prev = new->next->prev;
		new->next->prev = new;
		list->size++;

		return cursor;
	}

	/* if the cursor si somewhere in the middle */
	if (cursor->next != NULL) {
		new->next = cursor->next;
		cursor->next = new;
		new->prev = new->next->prev;
		new->next->prev = new;
		list->size++;

	} else {
		/* if the cursor points to the tail*/
		cursor->next = new;
		new->prev = cursor;
		list->tail = new;
		list->size++;
	}

	return cursor;
}

struct Node* DEL_FIRST(struct DoublyLinkedList *list,
	struct Node *cursor, FILE *out){
	if (list->size == 0) {
		fprintf(out, "Error: delete from empty playlist\n");
		return cursor;
	}

	if (list->size == 1) {
		delete_node(list, list->head);

		return NULL;
	}

	if (cursor == list->head) {
		cursor = list->head->next;
		delete_node(list, list->head);

		return cursor;
	}

	delete_node(list, list->head);

	return cursor;
}

struct Node* DEL_LAST(struct DoublyLinkedList *list,
	struct Node *cursor, FILE *out){
	if (list->size == 0) {
		fprintf(out, "Error: delete from empty playlist\n");
		return cursor;
	}

	if (list->size == 1) {
		delete_node(list, list->head);
		init_list(list);

		return NULL;
	}

	if (cursor == list->tail) {
		cursor = list->tail->prev;
		delete_node(list, list->tail);

		return cursor;
	}

	delete_node(list, list->tail);

	return cursor;
}

struct Node* DEL_CURR(struct DoublyLinkedList *list,
	struct Node *cursor, FILE *out){
	struct Node *be_gone;

	if (cursor == NULL) {
		fprintf(out, "Error: no track playing\n");
		return cursor;
	}

	if (list->size == 0) {
		fprintf(out, "Error: delete from empty playlist\n");
		return cursor;
	}

	if (list->size == 1) {
		delete_node(list, list->head);
		init_list(list);

		return NULL;
	}

	if (cursor == list->head) {
		cursor = DEL_FIRST(list, cursor, out);
		return cursor;
	}

	if (cursor == list->tail) {
		cursor = DEL_LAST(list, cursor, out);
		return cursor;
	}

	be_gone = cursor;
	cursor = cursor->next;
	delete_node(list, be_gone);

	return cursor;
}

struct Node* DEL_SONG(struct DoublyLinkedList *list,
	char *song, struct Node *cursor, FILE *out){
	char *path;
	struct Node *curr;

	path = set_path(song);

	curr = list->head;

	if (list->size == 0) {
		fprintf(out, "Error: no song found to delete\n");
		free(path);
		return cursor;
	}

	while (curr->next != NULL) {
		if (strcmp(curr->track->path_to_song, path) == 0) {
			if (cursor == curr) {
				cursor = curr->next;
			}

			delete_node(list, curr);
			free(path);
			return cursor;
		}

		curr = curr->next;
	}

	if (strcmp(curr->track->path_to_song, path) == 0) {
		if (cursor == curr) {
			cursor = curr->prev;
		}

		delete_node(list, curr);
		free(path);
		return cursor;
	}

	free(path);
	fprintf(out, "Error: no song found to delete\n");
	return cursor;
}

struct Node* MOVE_NEXT(struct Node *cursor, FILE *out){
	if (cursor == NULL) {
		fprintf(out, "Error: no track playing\n");
		return NULL;
	}

	if (cursor->next == NULL && cursor->prev == NULL) {
		return cursor;
	}

	if (cursor->next != NULL) {
		cursor = cursor->next;
		return cursor;
	}

	return cursor;
}

struct Node* MOVE_PREV(struct Node *cursor, FILE *out){
	if (cursor == NULL) {
		fprintf(out, "Error: no track playing\n");
		return NULL;
	}

	if (cursor->next == NULL && cursor->prev == NULL) {
		return cursor;
	}

	if (cursor->prev != NULL) {
		cursor = cursor->prev;
		return cursor;
	}

	return cursor;
}

void SHOW_FIRST(struct DoublyLinkedList *list, FILE *out){
	if (list->size == 0) {
		fprintf(out, "Error: show empty playlist\n");
		return;
	}

	show_info(list->head, out);
}

void SHOW_LAST(struct DoublyLinkedList *list, FILE *out){
	if (list->size == 0) {
		fprintf(out, "Error: show empty playlist\n");
		return;
	}

	show_info(list->tail, out);
}

void SHOW_CURR(struct DoublyLinkedList *list,
	struct Node *cursor, FILE *out) {
	if (list->size == 0 || cursor == NULL) {
		fprintf(out, "Error: show empty playlist\n");
		return;
	}

	show_info(cursor, out);
}

void SHOW_PLAYLIST(struct DoublyLinkedList *list, FILE *out) {
	struct Node *curr; int i;

	if (list->size != 0) {
		curr = list->head;
	}

	fprintf(out, "[");

	if (list->size != 0) {
		while (curr->next != NULL) {
		    for (i = 0; i < 30; ++i) {
    			if (curr->track->title[i] != '\0') {
            		fprintf(out, "%c", curr->track->title[i]);
        		}
    		}

			fprintf(out, "; ");
			curr = curr->next;
		}

		    for (i = 0; i < 30; ++i) {
        		if (curr->track->title[i] != '\0') {
            		fprintf(out, "%c", curr->track->title[i]);
        		}
    		}
	}

	fprintf(out, "]\n");
}
