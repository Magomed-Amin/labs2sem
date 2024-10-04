#ifndef LAB_WORKS_2_TOOLS_H
#define LAB_WORKS_2_TOOLS_H

typedef enum {
    PLUS_MINUS,
    MUL_DIV,
    POWER,
    NONE
} Type;

int read_expression(Deque*);

int parse_expression(Deque*, BNode*);

int check_polynomial(BNode*, BNode*);

void transform(BNode*, BNode*, int);

Deque *from_tree(BNode*);

#endif
