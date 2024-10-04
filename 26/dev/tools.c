#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "tools.h"

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

void deque_push_front(int value, Deque *deq) {
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

void deque_push_back(int value, Deque *deq) {
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

int deque_insert_after(int target, int value, Deque *deq) {
    if (deque_is_empty(deq))
        return 0;

    int result = 0;
    Deque *temp = deque_create();

    while (!deque_is_empty(deq)) {
        deque_push_front(deque_pop_back(deq), temp);
        if (temp->tail->value == target) {
            deque_push_back(value, deq);
            result = 1;
            break;
        }
    }

    while (!deque_is_empty(temp))
        deque_push_back(deque_pop_front(temp), deq);

    free(temp);
    return result;
}

int deque_pop_front(Deque *deq) {
    int temp = deq->tail->value;
    delete(deq->tail, deq);
    return temp;
}

int  deque_pop_back(Deque *deq) {
    int temp = deq->head->value;
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
        int item = deque_pop_back(deq);
        printf("%d, ", item);
        deque_push_front(item, temp);
    }
    int item = deque_pop_back(deq);
    printf("%d]\n", item);
    deque_push_back(item, deq);
    while (!deque_is_empty(temp)) {
        deque_push_back(deque_pop_front(temp), deq);
    }
    free(temp);
}

int deque_size(Deque *deq) {
    return deq->size;
}

void deque_erase(Deque *deq) {
    while (!deque_is_empty(deq)) {
        deque_pop_back(deq);
    }
    free(deq);
}

Deque *quick_sort(Deque *deq) {
    if (deque_size(deq) < 2)
        return deq;

    Deque *temp = deque_create();

    for (int i = 0; i < deque_size(deq) / 2; i++)
        deque_push_front(deque_pop_back(deq), temp);

    int base_value = deque_pop_back(deq);
    Deque *small = deque_create();
    Deque *big = deque_create();

    while (deq->head != NULL) {
        if (deq->head->value >= base_value)
            deque_push_front(deque_pop_back(deq), big);
        else
            deque_push_front(deque_pop_back(deq), small);
    }
    while (!deque_is_empty(temp)) {
        if (temp->tail->value >= base_value)
            deque_push_front(deque_pop_front(temp), big);
        else
            deque_push_front(deque_pop_front(temp), small);
    }

    free(temp);

    Deque *t_small = quick_sort(small);
    Deque *t_big = quick_sort(big);

    if (deque_size(t_small) >= deque_size(t_big)) {
        deque_push_front(base_value, t_small);

        while (!deque_is_empty(t_big))
            deque_push_front(deque_pop_back(t_big), t_small);

        free(t_big);

        return t_small;
    } else {
        deque_push_back(base_value, t_big);

        while (!deque_is_empty(t_small))
            deque_push_back(deque_pop_front(t_small), t_big);

        free(t_small);

        return t_big;
    }
}











