/* Copyright Arina Emanuela Turcu 313CA */

#ifndef PLAYLIST_UTILS_H__
#define PLAYLIST_UTILS_H__

struct song *get_info(struct Node *this_node, char *song, FILE *out);

void show_info(struct Node *to_show, FILE *out);

void delete_node(struct DoublyLinkedList *list, struct Node *be_gone);

void init_list(struct DoublyLinkedList *list);

void free_list(struct DoublyLinkedList **pp_list);

char *set_path(char *song);

struct Node *check_double(struct DoublyLinkedList *list,
    struct Node *this_node);

#endif  /* PLAYLIST_UTILS_H__ */
