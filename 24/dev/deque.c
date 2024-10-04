#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "deque.h"

void delete(DequeNode *node, Deque *deq) {
    if (node->next != NULL && node->prev != NULL) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    } else if (node->next == NULL && node->prev != NULL) {
        node->prev->next = NULL;
        deq->tail = node->prev;
    }
    else if (node->next != NULL) {
        node->next->prev = NULL;
        deq->head = node->next;
    }
    deq->size--;
    if (deq->size == 0)
        deq->head = deq->tail = NULL;
    free(node);
}

Deque *deque_create(void) {
    Deque *list = (Deque*)malloc(sizeof(Deque));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

bool deque_is_empty(Deque *deq) {
    return deq->size == 0;
}

void deque_push_front(String *value, Deque *deq) {
    DequeNode *element = (DequeNode*)malloc(sizeof(DequeNode));
    element->next = NULL;
    element->value = value;

    if (deq->head == NULL) {
        deq->head = deq->tail = element;
        element->prev = NULL;
        deq->size = 1;
        return;
    }

    deq->tail->next = element;
    element->prev = deq->tail;
    deq->tail = element;
    deq->size++;
}

void deque_push_back(String *value, Deque *deq) {
    DequeNode *element = (DequeNode*)malloc(sizeof(DequeNode));
    element->prev = NULL;
    element->value = value;

    if (deq->head == NULL) {
        deq->head = deq->tail = element;
        element->next = NULL;
        deq->size = 1;
        return;
    }

    deq->head->prev = element;
    element->next = deq->head;
    deq->head = element;
    deq->size++;
}

String *deque_pop_front(Deque *deq) {
    String *temp = deq->tail->value;
    delete(deq->tail, deq);
    return temp;
}

String *deque_pop_back(Deque *deq) {
    String *temp = deq->head->value;
    delete(deq->head, deq);
    return temp;
}

void deque_print(Deque *deq) {
    printf("[");
    if (!deq->size) {
        printf("]\n");
        return;
    }
    Deque *temp = deque_create();
    while (deque_size(deq) != 1) {
        String *item = deque_pop_back(deq);
        print(item);
        printf(", ");
        deque_push_front(item, temp);
    }
    String *item = deque_pop_back(deq);
    print(item);
    printf("]\n");
    deque_push_back(item, deq);
    while (!deque_is_empty(temp)) {
        deque_push_back(deque_pop_front(temp), deq);
    }
    free(temp);
}

void deque_print_expression(Deque *exp) {
    Deque *temp = deque_create();
    while (!deque_is_empty(exp)) {
        String *now = deque_pop_back(exp);
        if (deque_is_empty(temp) || (temp->tail->value->head->chr != '(' && now->head->chr != ')'))
            printf(" ");
        print(now);
        deque_push_front(now, temp);
    }
    while (!deque_is_empty(temp))
        deque_push_back(deque_pop_front(temp), exp);
    deque_erase(temp);
}

int deque_size(Deque *deq) {
    return deq->size;
}

void deque_erase(Deque *deq) {
    while (!deque_is_empty(deq)) {
        String *temp = deque_pop_back(deq);
        erase(temp);
    }
    free(deq);
}

