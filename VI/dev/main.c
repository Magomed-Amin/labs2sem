#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "computer.h"
#include "tools.h"


int main(int argc, char *argv[]){
    if (argc < 2) {
        usage();
        return 0;
    }

    char args[6] = {0, 0, 0, 0, 0, 0};
    for (int i = 0; i < argc; i++) {
        if (!strcmp(argv[i], "-g")) args[0] = 1;
        else if (!strcmp(argv[i], "-f")) args[1] = 1;
        else if (!strcmp(argv[i], "-i")) args[2] = 1;
        else if (!strcmp(argv[i], "-p")) args[3] = 1;
        else if (!strcmp(argv[i], "-d")) args[4] = 1;
        else if (!strcmp(argv[i], "-r")) args[5] = 1;
    }

    if (args[0]) {
        FILE* fileToRead = fopen("default.txt", "r");
        FILE* fileToWrite = fopen("database.dat", "a+");
        write_computer(fileToRead, fileToWrite);
    }

    if (args[1]) {
        char rowDivider[230];
        memset(rowDivider, '-', 230);
        FILE* file = fopen("database.dat", "r");
        if (!file)
            printf("Database is not exist\n");
        else
            printFile(file, rowDivider, false);
    }

    if (args[2])
        save_input_computer("database.dat");

    if (args[3]) {
        char rowDivider[230];
        memset(rowDivider, '-', 230);
        FILE* file = fopen("database.dat", "r");
        if (!file)
            printf("Database is not exist\n");
        else
            printFile(file, rowDivider, true);
    }

    if (args[4])
        remove("database.dat");

    if (args[5]) {
        srand(time(NULL));
        FILE* fileToWrite = fopen("database.dat", "a+");
        write_random_computer(fileToWrite, rand() % 10);
    }

    return 0;
}
