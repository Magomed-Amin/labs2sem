#include <stdio.h>
#include <string.h>

#include "tools.h"

int main(void) {
    char chr[15];
    Table *table = new_table();
    printf("Type 'help' to take info\n\n ");
    while (1) {
        printf("table> ");
        scanf("%s", chr);
        if (!strcmp(chr, "print")) {
            print_table(table);
            printf("\n ");
        } else if (!strcmp(chr, "add")) {
            if(add_row(table))
                printf(" OK\n\n ");
        } else if (!strcmp(chr, "random")) {
            int data;
            scanf("%d", &data);
            if (data + table->size > 10)
                printf(" Too many rows (max 10)!\n\n ");
            else {
                for (int i = 0; i < data; i++)
                    add_random_row(table);
                printf(" OK\n\n ");
            }
        } else if (!strcmp(chr, "sort")) {
            sort_table(table);
            printf(" OK\n\n ");
        } else if (!strcmp(chr, "erase")) {
            if (!table->size)
                printf(" Table already cleared.\n\n ");
            else {
                erase_table(table);
                table = new_table();
                printf(" OK\n\n ");
            }
        } else if (!strcmp(chr, "file")) {
            FILE *data = fopen("data.txt", "r");
            erase_table(table);
            table = new_table();
            read_from_file(data, table);
            fclose(data);
            printf(" OK\n\n ");
        } else if (!strcmp(chr, "reverse")) {
            reverse_table(table);
            printf(" OK\n\n ");
        } else if (!strcmp(chr, "search")) {
            printf(" Numeric part of key: ");
            int num = convert_to_int();
            printf(" String part of key: ");
            String *str = convert_to_string();
            String *res = bin_search(num, str, table);
            if (res == NULL)
                printf("\n Not found!\n\n ");
            else {
                printf("\n ");
                print(res);
                printf("\n\n  ");
            }
        } else if (!strcmp(chr, "mix")) {
            mix_table(table);
            printf(" OK\n\n ");
        } else if (!strcmp(chr, "exit")) return 0;
        else if (!strcmp(chr, "help")) {
            printf(" print : print list\n");
            printf(" add : add row to table\n");
            printf(" random <number> : generate number random rows (<= 10)\n");
            printf(" sort : sort table by keys\n");
            printf(" erase : erase table\n");
            printf(" file : upload table from source file 'data.txt'\n");
            printf(" reverse : reverse table\n");
            printf(" search : search data in table by key\n");
            printf(" mix : mix table randomly\n ");
            printf(" exit : complete the work\n\n ");
        } else
            printf(" Command not found!\n\n ");
    }
}
