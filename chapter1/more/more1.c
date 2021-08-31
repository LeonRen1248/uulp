#include <stdio.h>
#include <stdlib.h>

#define PAGELEN 24
#define LINELEN 512

int see_more() {
    printf("\033[7m --more?-- \033[m");
    int c;
    while ((c = getchar()) != EOF) {
        if (c == '\n') { // 再显示一行
            return 1;
        }
        if (c == ' ') { // 再显示一整页
            return PAGELEN;
        }
        if (c == 'q') { // 退出，不再显示
            return 0;
        }
    }

    return 0;
}

void do_more(FILE *fp) {
    char buffer[LINELEN];
    int cnt = 0;
    int reply = 0;
    while (fgets(buffer, LINELEN, fp) != NULL) {
        if (cnt >= PAGELEN) {
            reply = see_more();
            if (reply == 0) {
                break;
            }
            cnt -= reply;
        }
        if ((fputs(buffer, stdout)) == EOF) {
            exit(1);
        }
        cnt++;
    }
    if (reply) {
        fputs("\n", stdout); // 增加一个换行，使终端提示信息显示在新一行中
    }
}

int main(int argc, char const *argv[]) {
    FILE *fp;
    if (argc == 1) {
        do_more(stdin);
    }
    else {
        while (--argc) {
            if ((fp = fopen(*(++argv), "r")) != NULL) {
                do_more(fp);
                fclose(fp);
            }
            else {
                exit(1);
            }
        }
    }
    
    return 0;
}
