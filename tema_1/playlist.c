/* Copyright Arina Emanuela Turcu 313CA */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./commands.h"
#include "./playlist_utils.h"

void check_command(FILE *in, int n, struct DoublyLinkedList *list, FILE *out) {
	char command[NMAX], song[NMAX];
	struct Node* cursor;
	cursor = NULL;

	for (int i = 0; i < n; ++i) {
		fscanf(in, "%s", command);
		command[strlen(command)] = '\0';
		/* for ADD */
		if ( !strcmp(command, "ADD_FIRST") ) {
			fseek(in, SEEK_CUR, 1);
			fgets(song, 100, in);

			if (i != n - 1) {
				song[strlen(song) - 1] = '\0';
			}

			cursor = ADD_FIRST(list, song, cursor, out);
		}
		if ( !strcmp(command, "ADD_LAST") ) {
			fseek(in, SEEK_CUR, 1);
			fgets(song, 100, in);

			if (i != n - 1) {
				song[strlen(song) - 1] = '\0';
			}

			cursor = ADD_LAST(list, song, cursor, out);
		}
		if ( !strcmp(command, "ADD_AFTER") ) {
			fseek(in, SEEK_CUR, 1);
			fgets(song, 100, in);

			if (i != n - 1) {
				song[strlen(song) - 1] = '\0';
			}

			cursor = ADD_AFTER(list, song, cursor, out);
		}
		/* for DEL */
		if ( !strcmp(command, "DEL_FIRST") ) {
			cursor = DEL_FIRST(list, cursor, out);
		}
		if ( !strcmp(command, "DEL_LAST") ) {
			cursor = DEL_LAST(list, cursor, out);
		}
		if ( !strcmp(command, "DEL_CURR") ) {
			cursor = DEL_CURR(list, cursor, out);
		}
		if ( !strcmp(command, "DEL_SONG") ) {
			fseek(in, SEEK_CUR, 1);
			fgets(song, 100, in);

			if (i != n - 1) {
				song[strlen(song) - 1] = '\0';
			}

			cursor = DEL_SONG(list, song, cursor, out);
		}
		/* for MOVE */
		if ( !strcmp(command, "MOVE_NEXT") ) {
			cursor = MOVE_NEXT(cursor, out);
		}
		if ( !strcmp(command, "MOVE_PREV") ) {
			cursor = MOVE_PREV(cursor, out);
		}
		/* for SHOW */
		if ( !strcmp(command, "SHOW_FIRST") ) {
			SHOW_FIRST(list, out);
		}
		if ( !strcmp(command, "SHOW_LAST") ) {
			SHOW_LAST(list, out);
		}
		if ( !strcmp(command, "SHOW_CURR") ) {
			SHOW_CURR(list, cursor, out);
		}
		if ( !strcmp(command, "SHOW_PLAYLIST") ) {
			SHOW_PLAYLIST(list, out);
		}
	}
}

int main(int argc, char *argv[]) {
	FILE *in, *out;
	struct DoublyLinkedList *list;
	int n;

	if (argc != 3) {
		fprintf(stderr, "%s\n", "Error: este nevoie de 2 fisiere");
		return -1;
	}

	in = fopen(argv[1], "rt");
	out = fopen(argv[2], "wt");

	fscanf(in, "%d", &n);
	fseek(in, SEEK_CUR, 1);

	list = malloc(sizeof(struct DoublyLinkedList));

	if (list == NULL) {
		return -1;
	}

	init_list(list);

	check_command(in, n, list, out);

	fclose(in);
	fclose(out);
	free_list(&list);

	return 0;
}
