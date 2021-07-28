#include <stdio.h>
#include <stdlib.h>

#define PAGELEN 24
#define LINELEN 512

void do_more(FILE *fp);
int see_more();

int main(int argc, char *argv[]) {
    FILE *fp;
    if (argc == 1) {
        do_more(stdin);
    }
    while (--argc) {
        if ((fp = fopen(*(++argv), "r")) != NULL) {
            do_more(fp);
            fclose(fp);
        }
        else {
            exit(1);
        }
    }
    
    return 0;
}

void do_more(FILE *fp) {
    int num_line = 0, reply;
    char line[LINELEN];
    while (fgets(line, LINELEN, fp)) {
        if (num_line >= PAGELEN) {
            reply = see_more();
            if (reply == 0) {
                break;
            }
            else {
                num_line -= reply;
            }
        }
        if (fputs(line, stdout) == EOF) {
            exit(1);
        }
        num_line++;
    }
}

int see_more() {
    printf("\033[7m more? \033[m");
    char c;
    while (c = getchar()) {
        if (c == 'q')
            return 0;
        if (c == '\n')
            return 1;
        if (c == ' ')
            return PAGELEN;
    }
    return 0;
}