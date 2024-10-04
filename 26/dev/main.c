#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tools.h"

int main() {
    char chr[15];
    Deque *deq = deque_create();
    printf("Type 'help' to take info\n\n ");
    while (1) {
        printf("deq> ");
        scanf("%s", chr);
        if (!strcmp(chr, "push_front")) {
            int data;
            scanf("%d", &data);
            deque_push_front(data, deq);
            printf(" OK\n\n ");
        }
        else if (!strcmp(chr, "push_back")) {
            int data;
            scanf("%d", &data);
            deque_push_back(data, deq);
            printf(" OK\n\n ");
        }
        else if (!strcmp(chr, "ins_after")) {
            int target, value;
            scanf("%d %d", &target, &value);
            if (deque_insert_after(target, value, deq))
                printf(" OK\n\n ");
            else
                printf(" Target not found!\n\n ");
        }
        else if (!strcmp(chr, "pop_front")) {
            if (deque_is_empty(deq)) {
                printf(" Deque is empty!\n\n ");
            } else {
                deque_pop_front(deq);
                printf(" OK\n\n ");
            }
        }
        else if (!strcmp(chr, "pop_back")) {
            if (deque_is_empty(deq)) {
                printf(" Deque is empty!\n\n ");
            } else {
                deque_pop_back(deq);
                printf(" OK\n\n ");
            }
        }
        else if (!strcmp(chr, "random")) {
            int data;
            scanf("%d", &data);
            for (int i = 0; i < data; i++) {
                deque_push_front(rand() % 10000, deq);
            }
            printf(" OK\n\n ");
        }
        else if (!strcmp(chr, "print")) {
            printf(" ");
            deque_print(deq);
            printf("\n ");
        }
        else if (!strcmp(chr, "is_empty")) {
            if (deque_is_empty(deq))
                printf(" EMPTY");
            else
                printf(" NOT EMPTY\n\n ");
        }
        else if (!strcmp(chr, "size")) {
            printf(" %d\n\n ", deque_size(deq));
        }
        else if (!strcmp(chr, "erase")) {
            if (deque_is_empty(deq)) {
                printf(" Deque is already empty!\n\n ");
            } else {
                deque_erase(deq);
                deq = deque_create();
                printf(" OK\n\n ");
            }
        }
        else if (!strcmp(chr, "qsort")) {
            deq = quick_sort(deq);
            printf(" OK\n\n ");
        }
        else if (!strcmp(chr, "exit")) return 0;
        else if (!strcmp(chr, "help")) {
            printf(" push_front <number> : add an item to the end of the deq\n");
            printf(" push_back <number> : add an item to the begin of the deq\n");
            printf(" pop_front : remove an item from the end of the deq\n");
            printf(" pop_back : remove an item from the begin of the deq\n");
            printf(" random <count> : generate a deq of count random elements\n");
            printf(" print : print deq in console\n");
            printf(" is_empty : checking deq for emptiness\n");
            printf(" size : print deq size\n");
            printf(" erase : clear deq\n");
            printf(" qsort : hoare sorting method\n");
            printf(" exit : complete the work\n\n ");
        } else
            printf(" Command not found!\n\n ");
    }
}
