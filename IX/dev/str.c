#include <stdlib.h>
#include <stdio.h>

#include "str.h"

Iterator *iterator(StringNode *node) {
    Iterator *iter = (Iterator*)malloc(sizeof(Iterator));
    iter->node = node;
    return iter;
}

void next(Iterator *iter) {
    iter->node = iter->node->next;
}

void add(char chr, String *str) {
    StringNode *node = (StringNode*)malloc(sizeof(StringNode));
    node->chr = chr;
    node->next = NULL;
    if (!str->size)
        str->head = str->tail = node;
    else {
        str->tail->next = node;
        str->tail = node;
    }
    str->size++;
}

String *string(void) {
    String *res = (String*)malloc(sizeof(String));
    res->head = res->tail = NULL;
    res->size = 0;
    return res;
}

String *convert_key(String *str) {
    String *key = string();
    Iterator *iter = iterator(str->head);
    int p = str->size > 4 ? 4 : str->size;
    for (int i = 0; i < p; i++) {
        add(iter->node->chr, key);
        next(iter);
    }
    return key;
}

String *random_string(int size) {
    String *res = string();
    while (res->size != size)
        add((char)(rand() % 70 + (int)'0'),res);
    return res;
}

void print(String *str) {
    Iterator *iter = iterator(str->head);
    while (iter->node != NULL) {
        printf("%c", iter->node->chr);
        next(iter);
    }
    free(iter);
}

void erase(String *str) {
    Iterator *iter = iterator(str->head);
    while (iter->node != NULL) {
        StringNode *temp = iter->node;
        next(iter);
        free(temp);
    }
    free(str);
    free(iter);
}

int compare(String *first, String *second) {
    if (first->size == second->size) {
        Iterator *f_iter = iterator(first->head);
        Iterator *s_iter = iterator(second->head);
        while (s_iter->node != NULL) {
            if (f_iter->node == NULL){
                free(f_iter);
                free(s_iter);
                return -1;
            }
            if (f_iter->node->chr > s_iter->node->chr) {
                free(f_iter);
                free(s_iter);
                return 1;
            }
            if (f_iter->node->chr < s_iter->node->chr) {
                free(f_iter);
                free(s_iter);
                return -1;
            }
            next(f_iter);
            next(s_iter);
        }
        free(f_iter);
        free(s_iter);
        return 0;
    }
    return 1;
}
