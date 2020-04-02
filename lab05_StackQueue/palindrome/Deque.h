#ifndef __DEQUE_H__
#define __DEQUE_H__

#include "../src/LinkedList.h"

struct Deque {
    struct LinkedList *list;
};

void init_deque(struct Deque *deque);

int get_size_deque(struct Deque *deque);

int is_empty_deque(struct Deque *deque);

void* front(struct Deque *deque);

void* back(struct Deque *deque);

void pop_front(struct Deque *deque);

void pop_back(struct Deque *deque);

void push_front(struct Deque *deque, void *new_data);

void push_back(struct Deque *deque, void *new_data);

void clear_deque(struct Deque *deque);

void purge_deque(struct Deque *deque);

#endif /* __DEQUE_H__ */