#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>

// #define PAGELEN 24
#define LINELEN 512

static int page_len; // 当前终端可显示区域的行数

// 为了解决 ls /bin | ./more.out 不会停止的问题，
// 修改键盘的输入为从 /dev/tty 中读取，而不是从标准输入中读取
int see_more(FILE *fp_tty) {
    printf("\033[7m --more?-- \033[m");
    int c;
    while ((c = fgetc(fp_tty)) != EOF) {
        if (c == 'n') { // 再显示一行
            return 1;
        }
        if (c == ' ') { // 再显示一整页
            return page_len;
        }
        if (c == 'q') { // 退出，不再显示
            return 0;
        }
    }

    return 0;
}

// 为了适配当前运行此程序终端的尺寸
void do_more(FILE *fp) {
    char buffer[LINELEN];
    int cnt = 0;
    int reply = 0;
    FILE *fp_tty = fopen("/dev/tty", "r");
    struct winsize window_size;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &window_size);
    page_len = window_size.ws_row - 1;
    while (fgets(buffer, LINELEN, fp) != NULL) {
        if (cnt >= page_len) {
            system("stty raw -echo"); // 使终端不回显，而且不需要输入回车即可响应
            reply = see_more(fp_tty);
            system("stty -raw echo"); // 恢复终端默认状态
            printf("\r\033[K"); // 退到行首，且清空光标后内容
            if (reply == 0) {
                break;
            }
            cnt -= reply;
        }
        if ((fputs(buffer, stdout)) == EOF) {
            goto __ERROR__; // 异常处理
        }
        size_t len = strlen(buffer);
        cnt += (len / window_size.ws_col) ;
        if (len % window_size.ws_col) {
            ++cnt;
        }
    }
    if (reply) {
        fputs("\n", stdout); // 增加一个换行，使 more 结束之后的终端提示信息显示在新一行中
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
