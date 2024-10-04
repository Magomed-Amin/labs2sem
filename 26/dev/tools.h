#ifndef LAB_WORKS_TOOLS_H
#define LAB_WORKS_TOOLS_H

#include <stdbool.h>

typedef struct deque_node {
    int value;
    struct deque_node *prev;
    struct deque_node *next;
} DequeNode;

typedef struct {
    DequeNode *head;
    DequeNode *tail;
    int size;
} Deque;

Deque *deque_create(void);

bool deque_is_empty(Deque*);

void deque_push_front(int, Deque*);

void deque_push_back(int, Deque*);

int deque_insert_after(int, int, Deque*);

int deque_pop_front(Deque*);

int deque_pop_back(Deque*);

int deque_size(Deque*);

void deque_print(Deque *);

void deque_erase(Deque*);

Deque *quick_sort(Deque*);

#endif
