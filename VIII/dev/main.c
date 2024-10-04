#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "list.h"
#include "tools.h"

int main(void) {
    char chr[15];
    List *list = create();
    printf("Type 'help' to take info\n\n ");
    while (1) {
        printf("list> ");
        scanf("%s", chr);
        if (!strcmp(chr, "print")) {
            printf(" ");
            print(list);
            printf("\n ");
        } else if (!strcmp(chr, "ins_end")) {
            insert_to_end(convert_to_input('\n'), list);
            printf(" OK\n\n ");
        } else if (!strcmp(chr, "ins_begin")) {
            insert_to_begin(convert_to_input('\n'), list);
            printf(" OK\n\n ");
        } else if (!strcmp(chr, "ins_after")) {
            int a = convert_to_input('\n');
            printf(" Type data: ");
            int b = convert_to_input('\n');
            if (insert_after(a, b, list))
                printf(" OK\n\n ");
            else
                printf(" Target not found!\n\n ");
        } else if (!strcmp(chr, "del_end")) {
            delete_end(list);
            printf(" OK\n\n ");
        } else if (!strcmp(chr, "del_begin")) {
            delete_begin(list);
            printf(" OK\n\n ");
        } else if (!strcmp(chr, "del")) {
            if (delete(convert_to_input('\n'), list))
                printf(" OK\n\n ");
            else
                printf(" Target not found!\n\n ");
        } else if (!strcmp(chr, "size")) {
            printf(" %d\n\n ", size(list));
        } else if (!strcmp(chr, "action")) {
            if (action(convert_to_input('\n'), list))
                printf(" List has been cleared.\n\n ");
            else
                printf(" Value is not in list.\n\n ");
        } else if (!strcmp(chr, "random")) {
            int count;
            scanf("%d", &count);
            srand(time(NULL));
            for (int i = 0; i < count; i++)
                insert_to_end(rand() % 1000, list);
            printf(" OK\n\n ");
        } else if (!strcmp(chr, "exit")) return 0;
        else if (!strcmp(chr, "help")) {
            printf(" print : print list\n");
            printf(" ins_begin <element> : insert an element to the begin of list\n");
            printf(" ins_end <element> : insert an element to the end of list\n");
            printf(" ins_after <target> <element> : insert an element after target in list\n");
            printf(" del <target> : delete target from the list\n");
            printf(" del_end : delete an element from the end of the list\n");
            printf(" del_begin : delete an element from the begin of the list\n");
            printf(" size : print size of the list\n");
            printf(" action <target> : clear list if target in list\n ");
        } else
            printf(" Command not found!\n\n ");
    }
}