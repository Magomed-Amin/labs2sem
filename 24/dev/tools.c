#include <stdio.h>
#include <stdlib.h>

#include "str.h"
#include "deque.h"
#include "tree.h"
#include "tools.h"

int is_operator_or_bracket(char chr) {
    char *this = "+-/*()^";
    for (int i = 0; i < 7; i++) {
        if (this[i] == chr)
            return 1;
    }
    return 0;
}

int read_expression(Deque *input) {
    int is_char = 0, was_space = 0;
    char chr;
    while ((chr = getchar()) != '\n') {
        if (chr == ' ' || chr == '\t') {
            was_space = 1;
            continue;
        }
        if (is_operator_or_bracket(chr)) {
            was_space = 0;
            String *now = string();
            now->is_operand = 0;
            add(chr, now);
            deque_push_front(now, input);
            is_char = 0;
        } else if (!is_operator_or_bracket(chr) && !is_char) {
            was_space = 0;
            String *now = string();
            now->is_operand = 1;
            add(chr, now);
            deque_push_front(now, input);
            is_char = 1;
        } else if (is_char) {
            if (was_space)
                return 0;
            was_space = 0;
            add(chr, input->tail->value);
        }
    }
    return 1;
}

int check_ops(Deque *exp, int mode) {
    Deque *temp = deque_create();
    int res = 0;
    while (!deque_is_empty(exp)) {
        deque_push_front(deque_pop_back(exp), temp);
        if (temp->tail->value->is_operand && !mode) {
            res = 1;
            break;
        }
        if (!temp->tail->value->is_operand && temp->tail->value->head->chr != '(' &&
            temp->tail->value->head->chr != ')' && mode) {
            res = 1;
            break;
        }
    }
    while (!deque_is_empty(temp))
        deque_push_back(deque_pop_front(temp), exp);
    deque_erase(temp);
    if (exp->size == 1 && mode)
        return 1;
    return res;
}

int check_no_ops_brackets(Deque *exp) {
    Deque *temp = deque_create();
    int res = 1;

    while (deque_size(exp) != 1) {
        deque_push_back(deque_pop_front(exp), temp);
        if (temp->head->value->head->chr == '(' && (exp->tail->value->is_operand || exp->tail->value->head->chr == ')'))
            res = 0;
        if (exp->tail->value->head->chr == ')' && temp->head->value->is_operand)
            res = 0;
        if (!res) break;
    }

    while (!deque_is_empty(temp))
        deque_push_front(deque_pop_back(temp), exp);

    deque_erase(temp);
    return res;
}

int check_extra_brackets(Deque *expr, int strict) {
    while ((expr->tail->value->head->chr == ')' && expr->head->value->head->chr == '(') || strict) {
        String *left_bracket, *right_bracket;
        if (!strict) {
            left_bracket = deque_pop_back(expr);
            right_bracket = deque_pop_front(expr);
        }
        int level = 0;
        Deque *temp = deque_create();
        while (!deque_is_empty(expr)) {
            deque_push_back(deque_pop_front(expr), temp);
            if (temp->head->value->head->chr == ')')
                level++;
            if (temp->head->value->head->chr == '(') {
                if (!level && !strict)
                    level = expr->size + 10;
                else
                    level--;
            }
        }
        while (!deque_is_empty(temp))
            deque_push_front(deque_pop_back(temp), expr);
        if (level) {
            if (!strict) {
                deque_push_back(left_bracket, expr);
                deque_push_front(right_bracket, expr);
            }
            deque_erase(temp);
            return 0;
        } else {
            if (!strict) {
                erase(left_bracket);
                erase(right_bracket);
            } else {
                deque_erase(temp);
                return 1;
            }
        }
        deque_erase(temp);
    }
    return 1;
}

int parse_expression(Deque *exp, BNode *tree) {
    if (!check_ops(exp, 0))
        return 0;

    check_extra_brackets(exp, 0);

    int minus_check = 0;

    if (exp->head->value->tail->chr == '-' && exp->head->next->value->tail->chr == '(') {
        deque_pop_back(exp);
        if (exp->head->value->tail->chr == '(' && exp->tail->value->tail->chr == ')') {
            check_extra_brackets(exp, 0);
            if (exp->head->value->tail->chr != '(') {
                deque_push_back(chr_string('('), exp);
                deque_push_back(chr_string('-'), exp);
                deque_push_back(chr_string('\t'), exp);
                exp->head->value->is_operand = 1;
                deque_push_front(chr_string(')'), exp);
                minus_check = -1;
            } else minus_check = 1;
        } else minus_check = 1;
    }

    if (!check_extra_brackets(exp, 1) || !check_ops(exp, 1))
        return 0;

    if (!check_no_ops_brackets(exp))
        return 0;

    if (exp->head->value->head->chr == '+') {
        deque_pop_back(exp);
        check_extra_brackets(exp, 0);
    }

    int brackets = 0, check_operator = 0;

    if (exp->head->value->tail->chr == '-' && minus_check != -1) {
        if (deque_size(exp) == 2) {
            insert('-', exp->tail->value);
            tree->value = copy_string(exp->tail->value);
            tree->is_brackets_minus = 1;
            return 1;
        }
        deque_pop_back(exp);
        insert('-', exp->head->value);
    }

    if (!(exp->head->value->is_operand || exp->head->value->head->chr == '(') ||
        !(exp->tail->value->is_operand || exp->tail->value->head->chr == ')'))
        return 0;

    if (deque_size(exp) == 1) {
        if (!exp->head->value->is_operand)
            return 0;
        tree->value = deque_pop_back(exp);
        return 1;
    }
    if (deque_size(exp) == 2 && exp->head->value->tail->chr == '-' && exp->tail->value->is_operand) {
        add(exp->tail->value->head->chr, exp->head->value);
        tree->value = exp->head->value;
        return 1;
    }

    Deque *temp = deque_create();
    Type type = NONE;
    DequeNode *base = NULL;

    while (!deque_is_empty(exp)) {
        deque_push_back(deque_pop_front(exp), temp);
        if (!temp->head->value->is_operand) {
            char c = temp->head->value->tail->chr;
            if (c == '(') {
                brackets--;
                check_operator = 0;
            }
            if (c == ')')
                brackets++;
            if (brackets || (c == '-' && deque_is_empty(exp)))
                continue;
            if ((c == '+' || c == '-') && type != PLUS_MINUS) {
                if (check_operator)
                    return 0;
                type = PLUS_MINUS;
                base = temp->head;
                check_operator = 1;
            }
            if ((c == '*' || c == '/') && type != PLUS_MINUS && type != MUL_DIV) {
                if (check_operator)
                    return 0;
                type = MUL_DIV;
                base = temp->head;
                check_operator = 1;
            }
            if (c == '^' && type != PLUS_MINUS && type != MUL_DIV && type != POWER) {
                if (check_operator)
                    return 0;
                type = POWER;
                base = temp->head;
                check_operator = 1;
            }
            if (c == ')')
                check_operator = 0;
        } else check_operator = 0;
    }

    while (temp->head != base) {
        deque_push_front(deque_pop_back(temp), exp);
    }

    if (minus_check == 1)
        deque_push_back(chr_string('-'), exp);

    tree->value = deque_pop_back(temp);
    tree->left = new_node(NULL);
    tree->left->parent = tree;
    tree->right = new_node(NULL);
    tree->right->parent = tree;

    if (!(parse_expression(exp, tree->left) & parse_expression(temp, tree->right))) {
        if (tree->left->value == NULL) {
            erase_tree(tree->left);
            tree->left = NULL;
        }
        if (tree->right->value == NULL) {
            erase_tree(tree->right);
            tree->right = NULL;
        }
        return 0;
    }
    deque_erase(temp);
    return 1;
}

int check_polynomial(BNode *tree, BNode *var) {
    if (equal_trees(tree, var))
        return 1;
    if (tree->value->head->chr == '^' && (var_inside(tree->right, var) || (
            !equal_trees(tree->left, var) &&var_inside(tree->left, var))))
        return 0;
    if (tree->value->head->chr == '/' && var_inside(tree, var))
        return 0;
    if (tree->value->head->chr == '*') {
        if (var_inside(tree->left, var) && var_inside(tree->right, var))
            return 0;
        if (var_inside(tree->left, var)) {
            if (equal_trees(tree->left, var) || (tree->left->value->head->chr == '^' &&
                                                 equal_trees(tree->left->left, var) && !var_inside(tree->left->right, var)))
                return 1;
            return 0;
        }
        if (var_inside(tree->right, var)) {
            if (equal_trees(tree->right, var) || (tree->right->value->head->chr == '^' &&
                                                  equal_trees(tree->right->left, var) && !var_inside(tree->right->right, var)))
                return 1;
            return 0;
        }
        return 1;
    }

    if (tree->value->head->chr == '*') {
        if (!var_inside(tree->right, var) && equal_trees(tree->left, var))
            return 1;
        return 0;
    }
    if (tree->value->head->chr == '+' || tree->value->tail->chr == '-')
        return check_polynomial(tree->left, var) && check_polynomial(tree->right, var);
    return 1;
}

void add_star(BNode *exp) {
    if (exp->value->size > 1) {
        erase(exp->value);
        exp->value = string();
        add('*', exp->value);
    } else exp->value->head->chr = '*';
}

void transform(BNode* exp, BNode *var, int mode) {
    if (!var_inside(exp, var)) {
        if (!mode) {
            erase_tree(exp->left);
            erase_tree(exp->right);
            exp->left = exp->right = NULL;
            exp->value = chr_string('0');
        } else {
            BNode *e = copy_tree(exp);
            erase(exp->value);
            exp->value = chr_string('-');
            erase_tree(exp->left);
            erase_tree(exp->right);
            exp->left = e;
            exp->left->parent = exp;
            exp->right = new_node(chr_string('0'));
            exp->right->parent = exp;
        }
    } else if (equal_trees(exp, var) && mode) {
        add_star(exp);
        erase_tree(exp->left);
        exp->left = new_node(chr_string('-'));
        exp->left->parent = exp;
        exp->left->left = new_node(chr_string('1'));
        exp->left->left->parent = exp->left;
        exp->left->right = new_node(chr_string('1'));
        exp->left->right->parent = exp->left;
        erase_tree(exp->right);
        exp->right = copy_tree(var);
        exp->right->parent = exp;
    } else if (equal_trees(exp->left, var) && exp->value->head->chr == '^') {
        erase_tree(exp->left);
        if (!mode) {
            exp->left = copy_tree(exp->right);
            exp->left->parent = exp;
            add_star(exp);
            erase_tree(exp->right);
            exp->right = new_node(chr_string('^'));
            exp->right->parent = exp;
            exp->right->right = copy_tree(exp->left);
        } else {
            BNode *power = copy_tree(exp->right);
            exp->left = new_node(chr_string('-'));
            exp->left->left = new_node(chr_string('1'));
            exp->left->left->parent = exp->left;
            exp->left->right = copy_tree(exp->right);
            exp->left->right->parent = exp->left;
            exp->left->parent = exp;
            add_star(exp);
            erase_tree(exp->right);
            exp->right = new_node(chr_string('^'));
            exp->right->parent = exp;
            exp->right->right = power;
        }
        exp->right->right->parent = exp->right;
        exp->right->left = copy_tree(var);
        exp->right->left->parent = exp->right;
    } else if (equal_trees(exp->left, var) && exp->value->head->chr == '*') {
        if (!mode) {
            erase_tree(exp->right);
            exp->right = new_node(chr_string('1'));
            exp->right->parent = exp;
        } else {
            BNode *minus = new_node(chr_string('-'));
            minus->left = copy_tree(exp->right);
            minus->left->parent = minus;
            minus->right = new_node(chr_string('1'));
            minus->right->parent = minus;
            erase_tree(exp->right);
            exp->right = minus;
            exp->right->parent = exp;
        }
    } else if (equal_trees(exp->right, var) && exp->value->head->chr == '*') {
        if (!mode) {
            erase_tree(exp->left);
            exp->left = new_node(chr_string('1'));
            exp->left->parent = exp;
        } else {
            BNode *minus = new_node(chr_string('-'));
            minus->left = copy_tree(exp->left);
            minus->left->parent = minus;
            minus->right = new_node(chr_string('1'));
            minus->right->parent = minus;
            erase_tree(exp->left);
            exp->left = minus;
            exp->left->parent = exp;
        }
    } else if (exp->value->head->chr == '*' && var_inside(exp->right, var)) {
        if (!mode) {
            erase_tree(exp->left);
            exp->left = copy_tree(exp->right->right);
            exp->left->parent = exp;
        } else {
            BNode *minus = new_node(chr_string('-'));
            minus->left = copy_tree(exp->left);
            minus->left->parent = minus;
            minus->right = copy_tree(exp->right->right);
            minus->right->parent = minus;
            erase_tree(exp->left);
            exp->left = minus;
            exp->left->parent = exp;
        }
    } else if (exp->value->head->chr == '*' && var_inside(exp->left, var)) {
        if (!mode) {
            erase_tree(exp->right);
            exp->right = copy_tree(exp->left->right);
            exp->right->parent = exp;
        } else {
            BNode *minus = new_node(chr_string('-'));
            minus->left = copy_tree(exp->right);
            minus->left->parent = minus;
            minus->right = copy_tree(exp->left->right);
            minus->right->parent = minus;
            erase_tree(exp->right);
            exp->right = minus;
            exp->right->parent = exp;
        }
    } else if (exp->value->head->chr == '+' || exp->value->tail->chr == '-') {
        BNode *check = NULL;
        if (equal_trees(exp->right, var))
            check = exp->right;
        if (equal_trees(exp->left, var))
            check = exp->left;
        if (check != NULL && mode) {
            add_star(check);
            erase_tree(check->left);
            check->left = new_node(chr_string('-'));
            check->left->parent = check;
            check->left->left = new_node(chr_string('1'));
            check->left->left->parent = check->left;
            check->left->right = new_node(chr_string('1'));
            check->left->right->parent = check->left;
            erase_tree(check->right);
            check->right = copy_tree(var);
            check->right->parent = check;
        }
        if (check != exp->left)
            transform(exp->left, var, mode);
        if (check != exp->right)
            transform(exp->right, var, mode);
    }
}

Type type_op(char op) {
    if (op == '+' || op == '-')
        return PLUS_MINUS;
    if (op == '*' || op == '/')
        return MUL_DIV;
    if (op == '^')
        return POWER;
    return NONE;
}

Deque *from_tree(BNode *exp) {
    Deque *res = deque_create();
    if (exp->value->head->chr != '\t')
        deque_push_front(copy_string(exp->value), res);
    if (exp->left == NULL) {
        if (exp->is_brackets_minus && exp->parent != NULL) {
            deque_push_back(chr_string('('), res);
            deque_push_front(chr_string(')'), res);
        }
        return res;
    }

    Deque *left = from_tree(exp->left);
    Deque *right = from_tree(exp->right);

    while (!deque_is_empty(left))
        deque_push_back(deque_pop_front(left), res);
    while (!deque_is_empty(right))
        deque_push_front(deque_pop_back(right), res);

    deque_erase(left);
    deque_erase(right);

    if (exp->parent != NULL) {
        if (type_op(exp->parent->value->head->chr) > type_op(exp->value->head->chr) ||
            (exp->parent->value->tail->chr == '-' && exp == exp->parent->right &&
             !type_op(exp->value->head->chr))) {
            deque_push_back(chr_string('('), res);
            deque_push_front(chr_string(')'), res);
        }
    }
    return res;
}