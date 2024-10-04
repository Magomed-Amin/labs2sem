#ifndef LAB_WORKS_2_LIST_H
#define LAB_WORKS_2_LIST_H

typedef struct list_node {
    int data;
    struct list_node *next;
} ListNode;

typedef struct {
    ListNode *head;
    int size;
} List;

typedef struct {
    ListNode *node;
} Iterator;

List* create(void);

void next(Iterator*);

Iterator *iterator(ListNode*);

void print(List*);

void insert_to_begin(int, List*);

int insert_after(int, int, List*);

void insert_to_end(int, List*);

void delete_end(List *list);

int delete(int, List*);

void delete_begin(List*);

int size(List*);

int action(int, List*);

#endif
