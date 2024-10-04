#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "tools.h"

int convert_to_int(void) {
    char inp[100], ch;
    int i = 0;

    for (int j = 0; j < 100; j++)
        inp[j] = '.';
    getchar();
    while ((ch = getchar()) != '\n') {
        inp[i] = ch;
        i++;
    }

    return (int)strtol(inp, NULL, 10);
}

String *convert_to_string(void) {
    String *data = string();
    char chr;
    while ((chr = getchar()) != '\n')
        add(chr, data);
    return data;
}

int num_length(int num) {
    if (!num) return 1;
    int res = 0;
    while (num) {
        num /= 10;
        res++;
    }
    return res;
}

void spaces(int count) {
    for (int i = 0; i < count; i++)
        printf(" ");
}

Table *new_table(void) {
    Table *table = (Table*)malloc(sizeof(Table));
    for (int i = 0; i < 10; i++)
        table->rows[i] = NULL;
    table->size = 0;
    return table;
}

int check_key(int num_part, String *str_part, Table* table) {
    if (table->size)
        for (int i = 0; i < table->size; i++)
            if (table->rows[i]->key->num_part == num_part && !compare(str_part, table->rows[i]->key->str_part))
                return 1;
    return 0;
}

void add_random_row(Table *table) {
    String *rand_str = random_string(4);
    int rand_num = rand() % 100000;
    while (check_key(rand_num, rand_str, table)) {
        free(rand_str);
        rand_str = random_string(4);
        rand_num = rand() % 100000;
    }
    srand(time(NULL) % rand() % (rand() % 10000));
    Row *row = (Row*)malloc(sizeof(Row));
    row->key = (Key*)malloc(sizeof(Key));
    row->key->str_part = rand_str;
    row->key->num_part = rand_num;
    row->data = random_string(rand() % 15 + 2);
    table->rows[table->size] = row;
    table->size++;
}

int add_row(Table *table) {
    if (table->size == 10) {
        printf(" Table overflow!\n\n ");
        return 0;
    }
    Row *row = (Row*)malloc(sizeof(Row));
    row->key = (Key*)malloc(sizeof(Key));
    printf(" Type numeric part of key: ");
    int num_key = convert_to_int();
    printf(" Type string part of key (4 chars): ");

    String *str_key = convert_key(convert_to_string());

    if (check_key(num_key, str_key, table)) {
        printf(" The entered key already exists.\n\n ");
        free(str_key);
        free(row->key);
        free(row);
        return 0;
    }

    printf("Type data: ");
    row->key->num_part = num_key;
    row->key->str_part = str_key;

    String *data = convert_to_string();

    row->data = data;

    table->rows[table->size] = row;
    table->size++;
    printf("\n ");
    return 1;
}

void print_table(Table *table) {
    if (!table->size) {
        printf(" EMPTY\n  ");
        return;
    }
    int a = 0, b = 0, c = 0;
    for (int i = 0; i < table->size; i++) {
        if (num_length(table->rows[i]->key->num_part) > a)
            a = num_length(table->rows[i]->key->num_part);
        if (table->rows[i]->key->str_part->size > b)
            b = table->rows[i]->key->str_part->size;
        if (table->rows[i]->data->size > c)
            c = table->rows[i]->data->size;
    }

    printf(" ");
    for (int i = 0; i < table->size; i++) {
        printf(" ");
        printf("| ");
        spaces(a - num_length(table->rows[i]->key->num_part));
        printf("%d - ", table->rows[i]->key->num_part);
        print(table->rows[i]->key->str_part);
        spaces(b - table->rows[i]->key->str_part->size);
        printf(" | ");
        print(table->rows[i]->data);
        spaces(c - table->rows[i]->data->size);
        printf(" |\n ");
    }
}

void replace(int first, int second, Table *table) {
    Row *temp = table->rows[first];
    table->rows[first] = table->rows[second];
    table->rows[second] = temp;
}

void reverse_table(Table *table) {
    if (table->size > 1)
        for (int i = 0; i < table->size / 2; i++)
            replace(i, table->size - i - 1, table);
}

void sort_table(Table *table) {
    int i = 0;
    while (i != table->size) {
        int min_index = i;
        Row *min_row = table->rows[i];
        for (int j = i + 1; j < table->size; j++) {
            if ((table->rows[j]->key->num_part < min_row->key->num_part) || (
                    table->rows[j]->key->num_part == min_row->key->num_part &&
                    compare(table->rows[j]->key->str_part, min_row->key->str_part) == -1)) {
                min_row = table->rows[j];
                min_index = j;
            }
        }
        replace(i, min_index, table);
        i++;
    }
}

void erase_table(Table *table) {
    for (int i = 0; i < table->size; i++) {
        erase(table->rows[i]->key->str_part);
        free(table->rows[i]->key);
        erase(table->rows[i]->data);
        free(table->rows[i]);
    }
    free(table);
}

void mix_table(Table *table) {
    if (table->size > 1) {
        srand(time(NULL));
        for (int i = rand() % (table->size - 1); i < table->size; i += rand() % 3)
            replace(i, table->size - i - 1, table);
    }
}

void read_from_file(FILE *input, Table *table) {
    int chr = fgetc(input);
    int num = 0;

    while (chr != EOF) {
        char num_key[100];
        for (int i = 0; i < 100; i++)
            num_key[i] = ' ';
        int i = 0;

        while (chr != '\t') {
            if (chr == EOF) break;
            num_key[i] = chr;
            chr = fgetc(input);
            i++;
        }

        if (chr == EOF) break;

        String *str_key = string();
        chr = fgetc(input);

        while (chr != '\t') {
            add(chr, str_key);
            chr = fgetc(input);
        }

        String *data = string();
        chr = fgetc(input);

        while (chr != '\n' && chr != EOF) {
            add(chr, data);
            chr = fgetc(input);
        }
        if (check_key((int)strtol(num_key, NULL, 10), convert_key(str_key), table)) {
            printf(" Detected key already exist! Element was skipped.\n ");
            free(str_key);
            continue;
        }

        Row *row = (Row*)malloc(sizeof(Row));
        row->key = (Key*)malloc(sizeof(Key));
        row->key->num_part = (int)strtol(num_key, NULL, 10);
        row->key->str_part = convert_key(str_key);
        row->data = data;
        table->rows[num] = row;
        table->size++;
        num++;
        if (num > 9) {
            printf(" Table was overflowed!\n ");
            return;
        }
    }
}

int comb_compare(int i_first, String *s_first, int i_sec, String *s_sec) {
    if ((i_first > i_sec) || (i_first == i_sec && compare(s_first, s_sec) == 1))
        return 1;
    if ((i_first < i_sec) || (i_first == i_sec && compare(s_first, s_sec) == -1))
        return -1;
    return 0;
}

String *bin_search(int num_part, String *str_part, Table *table) {
    if (!table->size)
        return NULL;

    sort_table(table);
    int down = 0, top = table->size;
    int temp_down = down, temp_top = top;

    while (1) {
        if (comb_compare(num_part, str_part, table->rows[down]->key->num_part,
                         table->rows[down]->key->str_part) == -1)
            return NULL;

        if (comb_compare(num_part, str_part, table->rows[top - 1]->key->num_part,
                         table->rows[top - 1]->key->str_part) == 1)
            return NULL;

        if (!comb_compare(num_part, str_part, table->rows[down]->key->num_part,
                          table->rows[down]->key->str_part))
            return table->rows[down]->data;

        if (!comb_compare(num_part, str_part, table->rows[top - 1]->key->num_part,
                          table->rows[top - 1]->key->str_part))
            return table->rows[top - 1]->data;

        if (!comb_compare(num_part, str_part, table->rows[top / 2]->key->num_part,
                          table->rows[top / 2]->key->str_part))
            return table->rows[top / 2]->data;

        if (comb_compare(num_part, str_part, table->rows[top / 2]->key->num_part,
                         table->rows[top / 2]->key->str_part) <= 0 &&
                         comb_compare(num_part, str_part, table->rows[down]->key->num_part,
                                      table->rows[down]->key->str_part) == 1)
            top = top / 2;

        else if (comb_compare(num_part, str_part, table->rows[top / 2]->key->num_part,
                              table->rows[top / 2]->key->str_part) >= 0 &&
                 comb_compare(num_part, str_part, table->rows[top - 1]->key->num_part,
                              table->rows[top - 1]->key->str_part) == -1)
            down = top / 2 + 1;

        if (top - down < 2 || (temp_down == down && temp_top == top))
            return NULL;

        temp_top = top;
        temp_down = down;
    }
}
