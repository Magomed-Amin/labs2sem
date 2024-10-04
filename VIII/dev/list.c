#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "tools.h"

List *create(void) {
    List *list = (List*)malloc(sizeof(List));
    list->head = NULL;
    list->size = 0;
    return list;
}

void next(Iterator *iter) {
    iter->node = iter->node->next;
}

Iterator *iterator(ListNode *node) {
    Iterator *iter = (Iterator*)malloc(sizeof(Iterator));
    iter->node = node;
    return iter;
}

void print(List *list) {
    printf("[");
    if (list->size == 0) {
        printf("]\n");
        return;
    }
    Iterator *iter = iterator(list->head);
    while (iter->node->next != NULL) {
        convert_to_output(iter->node->data);
        printf(", ");
        next(iter);
    }
    convert_to_output(iter->node->data);
    printf("]\n");
}

void insert_to_end(int data, List *list) {
    ListNode *elem = (ListNode*)malloc(sizeof(ListNode));
    elem->next = NULL;
    elem->data = data;
    if (list->size == 0) {
        list->head = elem;
        list->size++;
        return;
    }
    Iterator *iter = iterator(list->head);
    while (iter->node->next != NULL) {
        next(iter);
    }
    iter->node->next = elem;
    list->size++;
}

int insert_after(int target, int data, List *list) {
    if (size(list) == 0)
        return 0;
    ListNode *elem = (ListNode*)malloc(sizeof(ListNode));
    elem->data = data;
    Iterator *iter = iterator(list->head);
    while (iter->node != NULL) {
        if (iter->node->data == target) {
            elem->next = iter->node->next;
            iter->node->next = elem;
            list->size++;
            return 1;
        }
        next(iter);
    }
    return 0;
}

void insert_to_begin(int data, List *list) {
    if (size(list) == 0)
        insert_to_end(data, list);
    else {
        ListNode *elem = (ListNode*)malloc(sizeof(ListNode));
        elem->data = data;
        elem->next = list->head;
        list->head = elem;
        list->size++;
    }
}

void delete_end(List *list) {
    if (list->size == 0)
        return;
    if (list->size == 1) {
        free(list->head);
        list->head = NULL;
        list->size--;
        return;
    }
    Iterator *iter = iterator(list->head);
    while (iter->node->next->next != NULL) {
        next(iter);
    }
    ListNode *temp = iter->node->next;
    iter->node->next = NULL;
    free(temp);
    list->size--;
}

int delete(int target, List *list) {
    if (size(list) == 0)
        return 0;
    if (list->head->data == target) {
        ListNode *temp = list->head;
        list->head = list->head->next;
        free(temp);
        list->size--;
        return 1;
    }
    Iterator *iter = iterator(list->head);
    while (iter->node != NULL) {
        if (iter->node->next->data == target) {
            ListNode *temp = iter->node->next;
            iter->node->next = iter->node->next->next;
            free(temp);
            list->size--;
            return 1;
        }
        next(iter);
    }
    return 0;
}

void delete_begin(List *list) {
    delete(list->head->data, list);
}

int size(List *list) {
    return list->size;
}

int action(int target, List* list) {
    if (list->size == 0)
        return 1;
    int flag = 0;
    Iterator *iter = iterator(list->head);
    while (iter->node != NULL) {
        if (iter->node->data == target) {
            flag = 1;
            break;
        }
        next(iter);
    }
    if (flag) {
        while (list->head != NULL)
            delete_end(list);
        return 1;
    }
    return 0;
}