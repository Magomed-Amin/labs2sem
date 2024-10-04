#ifndef LAB_WORKS_LIB_H
#define LAB_WORKS_LIB_H

#define NODE_PREFIX "├──"
#define NODE_PREFIX_LAST "└──"
#define NODE_PREFIX_TOP_LEVEL "│   "

typedef struct node {
    int key;
    float value;
    struct node *left;
    struct node *right;
    struct node *parent;
} Node;

Node* create_node(int key);
Node* insert_node(Node* root, int key);
Node* get_min(Node* root);
Node* get_max(Node* root);
void print_tree(Node* root, int depth, int is_last_child);
Node* delete_node(Node* root, int key);
void clear_tree(Node* root);
int is_width_decreasing(Node* root);

#endif
