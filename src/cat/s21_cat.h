#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 2048

struct flag {
    int file;
    char *fName[SIZE];
    int b;
    int checkB;
    int e;
    int n;
    int s;
    int checkS;
    int t;
    int v;
};


int fEnter = 0;

int get_arg(char **input, struct flag *flags);
void check_GNU(char **input, struct flag *flags, int number);
void output(FILE *file, struct flag *flags);
void char_print(char ch, struct flag *flags);

#endif  // SRC_CAT_S21_CAT_H_
