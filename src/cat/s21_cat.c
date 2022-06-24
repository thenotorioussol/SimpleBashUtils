#include "s21_cat.h"

int main(int count, char **input) {
    struct flag flags = {0};
    if (count > 0) {
        if (get_arg(input, &flags)) {
            for (int i = 0; flags.fName[i]; i++) {
                FILE *file;
                file = fopen(flags.fName[i], "r");
                if (file) {
                    output(file, &flags);
                    fclose(file);
                } else {
                    printf("s21_cat: %s: No such file or directory\n", flags.fName[i]);
                }
            }
        }
    }
}

int get_arg(char **input, struct flag *flags) {
    int checkArg = 1;
    int j = 0;
    for (int i = 1; input[i]; i++) {
        if (input[i][0] == '-') {
            if (input[i][1] == 'e') {
                flags->e = 1;
                flags->v = 1;
            } else if (input[i][1] == 'n') {
                flags->n = 1;
            } else if (input[i][1] == 'b') {
                flags->b = 1;
            } else if (input[i][1] == 's') {
                flags->s = 1;
            } else if (input[i][1] == 't') {
                flags->t = 1;
                flags->v = 1;
            } else if (input[i][1] == 'v') {
                flags->v = 1;
            } else if (input[i][1] == 'E') {
                flags->e = 1;
            } else if (input[i][1] == 'T') {
                flags->t = 1;
            } else if (input[i][1] == '-') {
                check_GNU(input, flags, i);
            } else {
                printf("s21_cat: invalid option -- '%c'\n", input[i][1]);
                checkArg = 0;
            }
        } else {
            flags->file = 1;
            flags->fName[j] = input[i];
            j++;
        }
    }
    if (flags->b == 1) {
        flags->n = 0;
    }
    return checkArg;
}

void check_GNU(char **input, struct flag *flags, int number) {
    if (strcmp("--number-nonblank", input[number]) == 0) {
        flags->b = 1;
    } else if (strcmp("--number", input[number]) == 0) {
        flags->n = 1;
    } else if (strcmp("--squeeze-blank", input[number]) == 0) {
        flags->s = 1;
    }
}

void output(FILE *file, struct flag *flags) {
    char ch;
    while (fscanf(file, "%c", &ch) != EOF) {
        char_print(ch, flags);
    }
}

void char_print(char ch, struct flag *flags) {
    int null_str = 0;
    if (flags->s == 1 && flags->checkS == 0 && ch == '\n') {
        flags->checkS += 1;
    } else if (flags->checkS != 0 && ch == '\n') {
        flags->checkS += 1;
        null_str = 1;
    } else if (flags->checkS > 1 && ch != '\n') {
        flags->checkS = 0;
        if (flags->e == 1) {
            printf("$");
        }
        printf("\n");
        if (flags->n != 0) {
            printf("%6d\t", flags->n);
            flags->n += 1;
        }
    } else {
        flags->checkS = 0;
    }
    if (flags->n != 0 || flags->b != 0) {
        if (fEnter == 1) {
            printf("%6d\t", flags->n);
            flags->n += 1;
            fEnter = 0;
        }
        if (flags->n == 1) {
            printf("%6d\t", flags->n);
            flags->n += 1;
        }
        if (flags->b == 1) {
            printf("%6d\t", flags->b);
            flags->b += 1;
        }
        if (ch == '\n' && flags->n != 0 && !null_str) {
            fEnter = 1;
        }
        if (ch == '\n' && flags->b != 0) {
            flags->checkB += 1;
        }
        if (ch != '\n' && flags->checkB != 0 && flags->checkS == 0) {
            printf("%6d\t", flags->b);
            flags->checkB = 0;
            flags->b += 1;
        }
    }
    if (flags->e == 1 && ch == '\n' && !null_str) {
        printf("$");
    }
    if (flags->v == 1) {
        if (ch < 32 && ch != 9 && ch != 10) {
            printf("^");
            ch += 64;
        }
        if (ch == 127) {
            printf("^");
            ch = '?';
        }
    }
    if (flags->t == 1 && ch == '\t') {
        printf("^");
        ch = 'I';
    }
    if (!null_str) {
        printf("%c", ch);
    }
}
