#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#define SIZE 2048

struct flag {
    int e;
    int i;
    int v;
    int c;
    int l;
    int n;
    char *patern[SIZE];
    int countPatern;
    char *filename[SIZE];
    int countFile;
};

int get_arg(char **input, struct flag *flags);
int grep(FILE *file, struct flag *flags, int numFile);
int check_str(char *str, struct flag *flags, int numStr, int countOutput, int numFile);
int check_patern(char *str, struct flag *flags, int flagI);

#endif  // SRC_GREP_S21_GREP_H_
