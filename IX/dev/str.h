#ifndef LAB_WORKS_2_STR_H
#define LAB_WORKS_2_STR_H

typedef struct node {
    char chr;
    struct node *next;
} StringNode;

typedef struct {
    StringNode *head;
    StringNode *tail;
    int size;
} String;

typedef struct {
    StringNode *node;
} Iterator;

void add(char, String*);

String *string(void);

String *convert_key(String*);

String *random_string(int);

void print(String*);

void erase(String*);

int compare(String*, String*);

#endif
