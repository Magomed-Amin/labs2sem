#ifndef UNTITLED2_TOOLS_H
#define UNTITLED2_TOOLS_H

#include "stdbool.h"
#include "computer.h"

#define HEADER "=      Name = Num. of proc. =   Type of proc. =    Mem. cap. =   Video-contr. = " \
"Video mem. cap. = Video mem. type =   Num. of hard dr. =   Cap. of hard dr. =  Num. of integr. contr. =  " \
"Num. of ext. dev. =         OS =    Branded ="

char *VC(vc);

char *VMT(vmt);

vmt Vmt(const char[20]);

vc Vc(const char type[20]);

void write_computer(FILE*, FILE*);

void printPerson(Computer*);

void save_input_computer(char[20]);

void write_random_computer(FILE*, int);

void usage(void);

void printFile(FILE*, char[230], bool);

bool Branded(char[5]);

char *branded(bool);

#endif
