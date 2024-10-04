#ifndef LAB_WORKS_2_DEQUE_H
#define LAB_WORKS_2_DEQUE_H

#include <stdbool.h>
#include "str.h"

typedef struct deque_node {
    String *value;
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

void deque_push_front(String*, Deque*);

void deque_push_back(String*, Deque*);

String *deque_pop_front(Deque*);

String *deque_pop_back(Deque*);

int deque_size(Deque*);

void deque_print(Deque *);

void deque_print_expression(Deque*);

void deque_erase(Deque*);

#endif
