#include <stdio.h>
#include <stdlib.h>

#define PAGELEN 24
#define LINELEN 512

// 为了解决 ls /bin | ./more.out 不会停止的问题，
// 修改键盘的输入为从 /dev/tty 中读取，而不是从标准输入中读取
int see_more(FILE *fp_tty) {
    printf("\033[7m --more?-- \033[m");
    int c;
    while ((c = fgetc(fp_tty)) != EOF) {
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
    FILE *fp_tty = fopen("/dev/tty", "r");
    while (fgets(buffer, LINELEN, fp) != NULL) {
        if (cnt >= PAGELEN) {
            reply = see_more(fp_tty);
            if (reply == 0) {
                break;
            }
            cnt -= reply;
        }
        if ((fputs(buffer, stdout)) == EOF) {
            goto __ERROR__; // 异常处理
        }
        cnt++;
    }
    if (reply) {
        fputs("\n", stdout); // 增加一个换行，使终端提示信息显示在新一行中
    }
__ERROR__:
    if (fp_tty) {
        fclose(fp_tty);
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
