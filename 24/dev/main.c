#include <stdio.h>
#include <string.h>

#include "deque.h"
#include "tree.h"
#include "tools.h"

int main(void) {
    char chr[15];
    BNode *tree = NULL;
    BNode *var = new_node(chr_string('x'));
    printf("Type 'help' to take info\n\n ");
    while (1) {
        printf("expression> ");
        scanf("%s", chr);
        if (!strcmp(chr, "set")) {
            erase_tree(tree);
            scanf(" ");
            Deque *input = deque_create();
            tree = new_node(NULL);
            int ok1 = read_expression(input), ok2 = parse_expression(input, tree);
            if (!ok1 || !ok2) {
                erase_tree(tree);
                tree = NULL;
                printf("\n Incorrect!\n\n ");
            }
            else {
                printf("\n");
                deque_print_expression(from_tree(tree));
                printf("\n OK\n\n ");
            }

            deque_erase(input);
        } else if (!strcmp(chr, "print")) {
            if (tree == NULL)
                printf("\n NULL\n\n ");
            else {
                printf("\n");
                deque_print_expression(from_tree(tree));
                printf("\n\n ");
            }
        } else if (!strcmp(chr, "print-var")) {
            printf("\n");
            deque_print_expression(from_tree(var));
            printf("\n\n ");
        } else if (!strcmp(chr, "tree")) {
            if (tree == NULL)
                printf("\n NULL\n\n ");
            else {
                printf("\n ");
                show(tree, 0, 1, "fr");
                printf("\n ");
            }
        } else if (!strcmp(chr, "var")) {
            erase_tree(var);
            scanf(" ");
            Deque *input = deque_create();
            var = new_node(NULL);
            int ok1 = read_expression(input), ok2 = parse_expression(input, var);
            if (!ok1 || !ok2) {
                erase_tree(var);
                var = new_node(chr_string('x'));
                printf("\n Incorrect!\n\n ");
            }
            else {
                printf("\n");
                deque_print_expression(from_tree(var));
                printf("\n OK\n\n ");
            }
            deque_erase(input);
        } else if (!strcmp(chr, "trans-1")) {
            if (tree == NULL)
                printf("\n Expression is now NULL\n\n ");
            else {
                if (check_polynomial(tree, var)) {
                    transform(tree, var, 0);
                    printf("\n");
                    deque_print_expression(from_tree(tree));
                    printf("\n OK\n\n ");
                } else
                    printf("\n Expression is no polynomial!\n\n ");
            }
        } else if (!strcmp(chr, "trans-2")) {
            if (tree == NULL)
                printf("\n Expression is now NULL\n\n ");
            else {
                if (check_polynomial(tree, var)) {
                    transform(tree, var, 1);
                    printf("\n");
                    deque_print_expression(from_tree(tree));
                    printf("\n OK\n\n ");
                } else
                    printf("\n Expression is no polynomial!\n\n ");
            }
        } else if (!strcmp(chr, "exit")) return 0;
        else if (!strcmp(chr, "help")) {
            printf("\n set : set expression\n");
            printf(" var : set variable of polynomial\n");
            printf(" print : print expression\n");
            printf(" print-var : print variable of polynomial\n");
            printf(" tree : print expression tree\n");
            printf(" trans-1 : replace ai to i in polynomial\n");
            printf(" trans-2 : replace ai to ai - i in polynomial\n");
            printf(" exit : complete the work\n\n ");
        } else
            printf("\n Command not found!\n\n ");
    }
}
