/* Copyright Arina Emanuela Turcu 313CA */

#ifndef COMMANDS_H__
#define COMMANDS_H__

#define NMAX 100

struct Node {
    struct song *track;
    struct Node *prev;
    struct Node *next;
};

struct DoublyLinkedList {
    struct Node* head;
    struct Node* tail;
    int size;
};

struct song {
	char *path_to_song;
	char title[30];
	char artist[30];
	char album[30];
	char year[4];
};

struct Node* ADD_FIRST(struct DoublyLinkedList *list, char *song,
	struct Node *cursor, FILE *out);

struct Node* ADD_LAST(struct DoublyLinkedList *list, char *song,
	struct Node *cursor, FILE *out);

struct Node* ADD_AFTER(struct DoublyLinkedList *list, char *song,
	struct Node *cursor, FILE *out);

struct Node* DEL_FIRST(struct DoublyLinkedList *list,
	struct Node *cursor, FILE *out);

struct Node* DEL_LAST(struct DoublyLinkedList *list,
	struct Node *cursor, FILE *out);

struct Node* DEL_CURR(struct DoublyLinkedList *list,
	struct Node *cursor, FILE *out);

struct Node* DEL_SONG(struct DoublyLinkedList *list, char *song,
	struct Node *cursor, FILE *out);

struct Node* MOVE_NEXT(struct Node *cursor, FILE *out);

struct Node* MOVE_PREV(struct Node *cursor, FILE *out);

void SHOW_FIRST(struct DoublyLinkedList *list, FILE *out);

void SHOW_LAST(struct DoublyLinkedList *list, FILE *out);

void SHOW_CURR(struct DoublyLinkedList *list, struct Node *cursor, FILE *out);

void SHOW_PLAYLIST(struct DoublyLinkedList *list, FILE *out);

#endif  // COMMANDS_H__
