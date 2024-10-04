#ifndef LAB_WORKS_2_TOOLS_H
#define LAB_WORKS_2_TOOLS_H

#include "str.h"

typedef struct {
    String *str_part;
    int num_part;
} Key;

typedef struct {
    Key *key;
    String *data;
} Row;

typedef struct {
    Row *rows[10];
    int size;
} Table;

int convert_to_int(void);

String *convert_to_string(void);

Table *new_table(void);

void add_random_row(Table*);

int add_row(Table*);

void print_table(Table*);

void reverse_table(Table*);

void sort_table(Table*);

void erase_table(Table*);

void mix_table(Table*);

void read_from_file(FILE*, Table*);

String *bin_search(int, String*, Table*);

#endif
