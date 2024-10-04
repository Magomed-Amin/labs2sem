#include <stdio.h>
#include <stdlib.h>
#include "lib.h"

Node* create_node(int key) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Memory allocation error for the new node\n");
        exit(1);
    }
    new_node->key = key;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->parent = NULL;
    return new_node;
}

Node* insert_node(Node* root, int key) {
    if (root == NULL) {
        return create_node(key);
    }
    if (key < root->key) {
        root->left = insert_node(root->left, key);
    } else if (key > root->key) {
        root->right = insert_node(root->right, key);
    }
    return root;
}

Node* get_min(Node* root) {
    if (root == NULL) return NULL;
    if (root->left == NULL) return root;
    return get_min(root->left);
}

Node* get_max(Node* root) {
    if (root == NULL) return NULL;
    if (root->right == NULL) return root;
    return get_max(root->right);
}

void print_tree(Node* root, int depth, int is_last_child) {
    if (root == NULL) return;
    for (int i = 0; i < depth - 1; i++) {
        printf("%s", NODE_PREFIX_TOP_LEVEL);
    }

    if (depth) {
        if (is_last_child) {
            printf("%s", NODE_PREFIX_LAST);
        } else {
            printf("%s", NODE_PREFIX);
        }
    }

    printf("(%d)\n", root->key);
    print_tree(root->right, depth + 1, 0);
    print_tree(root->left, depth + 1, 1);
}

Node* delete_node(Node* root, int key) {
    if (root == NULL) return root;
    if (key < root->key) {
        root->left = delete_node(root->left, key);
    } else if (key > root->key) {
        root->right = delete_node(root->right, key);
    } else {
        // Нашли нужный узел

        // (1) Если у удаляемого узла нет левого дочернего узла
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            // Возвращаем правый дочерний узел (может быть NULL)
            return temp;
        // (2) Если у удаляемого узла нет правого дочернего узла
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            // Возвращаем левый дочерний узел (не NULL)
            return temp;
        }

        // (3) Если у удаляемого узла есть оба дочерних узла
        // Находим узел с минимальным ключом в правом поддереве
        Node* temp = root->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }
        // Копируем значение найденного узла в удаляемый узел
        root->key = temp->key;
        // Рекурсивно удаляем узел с минимальным ключом из правого поддерева
        root->right = delete_node(root->right, temp->key);
    }
    return root;
}

void clear_tree(Node* root) {
    if (root == NULL) return;
    clear_tree(root->left);
    clear_tree(root->right);
    free(root);
}

int is_width_decreasing(Node* root) {
    if (root == NULL) return 1;

    int prev_queue_size = -1;
    int queue_size;

    Node* current_node;
    Node** queue = (Node**)malloc(sizeof(Node*) * 1000);
    if (queue == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    int front = 0, rear = -1;

    queue[++rear] = root;

    while (1) {
        queue_size = rear - front + 1;
        if (prev_queue_size != -1 && prev_queue_size < queue_size) {
            free(queue);
            return 0;
        }
        prev_queue_size = queue_size;

        if (queue_size == 0) {
            break;
        }

        while (queue_size > 0) {
            current_node = queue[front++];
            queue_size--;

            if (current_node->left != NULL) {
                queue[++rear] = current_node->left;
            }
            if (current_node->right != NULL) {
                queue[++rear] = current_node->right;
            }
        }
    }

    free(queue);
    return 1;
}