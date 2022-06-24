#include "s21_grep.h"

int main(int count, char **input) {
    struct flag flags = {0};
    if (count > 2 && get_arg(input, &flags)) {
        for (int i = 0; flags.filename[i]; i++) {
            FILE *file;
            file = fopen(flags.filename[i], "r");
            if (file != NULL) {
                if (flags.l == 1 && grep(file, &flags, i) > 0) {
                    printf("%s\n", flags.filename[i]);
                } else if (flags.l != 1) {
                    if (flags.c == 1) {
                        if (flags.countFile > 1) {
                            printf("%s:%d\n", flags.filename[i], grep(file, &flags, i));
                        } else {
                            printf("%d\n", grep(file, &flags, i));
                        }
                    } else {
                        grep(file, &flags, i);
                    }
                }
                fclose(file);
            }
        }
    }
}

int get_arg(char **input, struct flag *flags) {
    int countPatern = 0;
    int countFile = 0;
    int countFlags = 1;
    for (int i = 1; input[i]; i++) {
        if (input[i][0] == '-') {
            if (input[i][1] == 'e') {
                flags->e = 1;
                i++;
                flags->patern[countPatern] = input[i];
                countPatern++;
            } else if (input[i][1] == 'i') {
                flags->i = 1;
            } else if (input[i][1] == 'v') {
                flags->v = 1;
            } else if (input[i][1] == 'c') {
                flags->c = 1;
            } else if (input[i][1] == 'l') {
                flags->l = 1;
            } else if (input[i][1] == 'n') {
                flags->n = 1;
            }
        } else if (countPatern == 0) {
            flags->patern[countPatern] = input[i];
            countPatern++;
        } else {
            flags->filename[countFile] = input[i];
            countFile++;
        }
        countFlags++;
    }
    flags->countPatern = countPatern;
    flags->countFile = countFile;
    return countFlags;
}

int grep(FILE *file, struct flag *flags, int numFile) {
    int i = 0;
    int countOutput = 0;
    int numStr = 1;
    char ch;
    char str[SIZE];
    while (fscanf(file, "%c", &ch) != EOF) {
        if (ch != '\n') {
            str[i] = ch;
            i++;
        } else {
            str[i] = '\0';
            countOutput = check_str(str, flags, numStr, countOutput, numFile);
            numStr++;
            i = 0;
        }
    }
    if (ch != '\n') {
        str[i] = '\0';
        countOutput = check_str(str, flags, numStr, countOutput, numFile);
    }
    return countOutput;
}

int check_str(char *str, struct flag *flags, int numStr, int countOutput, int numFile) {
    if ((check_patern(str, flags, flags->i) == 1)) {
        if (flags->countFile > 1) {
            if (flags->c == 1 || flags->l == 1) {
                countOutput++;
            } else if (flags->n == 1) {
                printf("%s:%d:%s\n", flags->filename[numFile], numStr, str);
            } else {
                printf("%s:%s\n", flags->filename[numFile], str);
            }
        } else {
            if (flags->c == 1  || flags->l == 1) {
                countOutput++;
            } else if (flags->n == 1) {
                printf("%d:%s\n", numStr, str);
            } else {
                printf("%s\n", str);
            }
        }
    }
    return countOutput;
}

int check_patern(char *str, struct flag *flags, int flagI) {
    int result = 0;
    for (int i = 0; flags->patern[i]; i++) {
        regex_t reg;
        regmatch_t pmatch[1];
        if (flagI == 1) {
            regcomp(&reg, flags->patern[i], REG_ICASE);
            if (regexec(&reg, str, 1, pmatch, 0) == 0) {
                result = 1;
            }
            regfree(&reg);
        } else {
            regcomp(&reg, flags->patern[i], 0);
            if (regexec(&reg, str, 1, pmatch, 0) == 0) {
                result = 1;
            }
            regfree(&reg);
        }
    }
    if (flags->v == 1 && result == 0) {
        result = 1;
    } else if (flags->v == 1 && result == 1) {
        result = 0;
    }
    return result;
}
