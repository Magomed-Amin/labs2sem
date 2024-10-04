#include <stdio.h>

#include "tools.h"

int power(int x, int y) {
    int t = x;
    if (!y) return 1;
    for (int i = 1; i < y; i++)
        x *= t;
    return x;
}

void convert_to_output(int data) {
    if (!data) {
        printf("0");
        return;
    }

    char res[100];
    for (int j = 0; j < 100; j++)
        res[j] = '.';

    int j = 0;
    while (data != 0) {
        if (data % 2)
            res[j] = '1';
        else
            res[j] = '0';
        j++;
        data /= 2;
    }

    for (int i = 99; i >= 0; i--) {
        if (res[i] == '0' || res[i] == '1')
            printf("%c", res[i]);
    }
}

int convert_to_input(char brk) {
    char inp[100], ch;
    int i = 0, pow = 0, res = 0;

    for (int j = 0; j < 100; j++)
        inp[j] = '.';

    while ((ch = getchar()) != brk) {
        inp[i] = ch;
        i++;
    }

    for (int j = 99; j >= 0; j--) {
        if (inp[j] == '1') {
            res += power(2, pow);
            pow++;
        } else if (inp[j] == '0')
            pow++;
    }

    return res;
}