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
    int is_operand;
} String;

typedef struct {
    StringNode *node;
} Iterator;

void add(char, String*);

void insert(char, String*);

String *string(void);

String *chr_string(char);

void print(String*);

void erase(String*);

int compare(String*, String*);

String *copy_string(String*);

#endif
