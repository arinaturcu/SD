/* Copyright Arina Emanuela Turcu 313CA */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./commands.h"
#include "./playlist_utils.h"

struct song *get_info(struct Node *this_node, char *song, FILE *out) {
    FILE *file;
    char buff, *path;

    this_node->track = malloc(sizeof(struct song));

    this_node->track->path_to_song = set_path(song);

    memset(this_node->track->title, '\0', 31);
    memset(this_node->track->artist, '\0', 31);
    memset(this_node->track->album, '\0', 31);
    memset(this_node->track->year, '\0', 5);

    path = this_node->track->path_to_song;

    file = fopen(path, "rb");

    if (file == NULL) {
        fprintf(out, "Error: file %s couldn't be opened.\n", path);
        return NULL;
    }

    fseek(file, -94, SEEK_END);

    for (int i = 0; i < 30; ++i) {
        fread(&buff, sizeof(char), 1, file);

        if (buff != '\0') {
            this_node->track->title[i] = buff;
        }
    }

    for (int i = 0; i < 30; ++i) {
        fread(&buff, sizeof(char), 1, file);

        if (buff != '\0') {
            this_node->track->artist[i] = buff;
        }
    }

    for (int i = 0; i < 30; ++i) {
        fread(&buff, sizeof(char), 1, file);

        if (buff != '\0') {
            this_node->track->album[i] = buff;
        }
    }

    for (int i = 0; i < 4; ++i) {
        fread(&buff, sizeof(char), 1, file);

        if (buff != '\0') {
            this_node->track->year[i] = buff;
        }
    }

    fclose(file);
    return this_node->track;
}

void show_info(struct Node *to_show, FILE *out) {
    int i;

    fprintf(out, "Title: ");

    for (i = 0; i < 30; ++i) {
        if (to_show->track->title[i] != '\0') {
            fprintf(out, "%c", to_show->track->title[i]);
        }
    }

    fprintf(out, "\nArtist: ");

    for (i = 0; i < 30; ++i) {
        if (to_show->track->artist[i] != '\0') {
            fprintf(out, "%c", to_show->track->artist[i]);
        }
    }

    fprintf(out, "\nAlbum: ");

    for (i = 0; i < 30; ++i) {
        if (to_show->track->album[i] != '\0') {
            fprintf(out, "%c", to_show->track->album[i]);
        }
    }

    fprintf(out, "\nYear: ");

    for (i = 0; i < 4; ++i) {
        if (to_show->track->year[i] != '\0') {
            fprintf(out, "%c", to_show->track->year[i]);
        }
    }
    fprintf(out, "\n");
}

void delete_node(struct DoublyLinkedList *list, struct Node *be_gone) {
    if (list->size == 1) {
        list->head = NULL;
        list->tail = NULL;

        be_gone->next = NULL;
        be_gone->prev = NULL;

        free(be_gone->track->path_to_song);
        free(be_gone->track);
        free(be_gone);

        list->size = 0;

        return;
    }

    if (be_gone == list->head) {
        list->head = be_gone->next;
        list->head->prev = NULL;

        free(be_gone->track->path_to_song);
        free(be_gone->track);
        free(be_gone);

        list->size--;

        return;
    }

    if (be_gone == list->tail) {
        list->tail->prev->next = NULL;
        list->tail = list->tail->prev;

        free(be_gone->track->path_to_song);
        free(be_gone->track);
        free(be_gone);

        list->size--;

        return;
    }

    be_gone->prev->next = be_gone->next;
    be_gone->next->prev = be_gone->prev;

    free(be_gone->track->path_to_song);
    free(be_gone->track);
    free(be_gone);

    list->size--;
}

void init_list(struct DoublyLinkedList *list) {
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void free_list(struct DoublyLinkedList **pp_list) {
    if ((*pp_list)->size == 0) {
        free(*pp_list);
        return;
    }

    while ((*pp_list)->size > 0) {
        delete_node(*(pp_list), (*pp_list)->head);
    }

    free(*pp_list);
}

/* creates path to the song file */
char *set_path(char *song) {
	char *path;

	path = malloc(sizeof(char) * NMAX);

    snprintf(path, NMAX, "./songs/");
    snprintf(path + strlen(path), NMAX - strlen(path), "%s", song);

	return path;
}

/* checks if the song is already in the playlist and returns that node*/
struct Node *check_double(struct DoublyLinkedList *list,
    struct Node *this_node) {
	struct Node *curr;

	curr = list->head;

    while (curr != NULL) {
    	if ( strcmp(curr->track->title, this_node->track->title) == 0 ) {
    		return curr;
    	}

		curr = curr->next;
    }

    return NULL;
}
