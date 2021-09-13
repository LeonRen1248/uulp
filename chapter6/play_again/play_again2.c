#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

#define PROMPT_ASK "Do you want another transaction(y/n)? "
#define PROMPT_WRONG_INPUT "Cannot understand last input, please try y(Y) or n(N): "

int get_response(const char *prompt) {
    int response = 1;
    printf("%s", prompt);
    while (1) {
        switch ( getchar() ) {
            case 'y':
            case 'Y': return 1;
            case 'n':
            case 'N':
            case EOF: return 0;
            // 不再提示错误信息，忽略错误输入
            // default: {
            //     putchar('\n');
            //     printf(PROMPT_WRONG_INPUT);
            // }
        }
    }
}

void set_cr_noecho_mode() {
    struct termios ttystate;
    tcgetattr(0, &ttystate);
    ttystate.c_lflag &= ~ICANON; // 不需要输入回车即可开始执行
    ttystate.c_lflag &= ~ECHO; // 不回显
    ttystate.c_cc[VMIN] = 1;
    tcsetattr(0, TCSANOW, &ttystate);
}

void tty_mode(int how) {
    static struct termios original_mode;
    if (how == 0) {
        tcgetattr(0, &original_mode); // Keep original mode
    }
    else {
        tcsetattr(0, TCSANOW, &original_mode); // Restore original mode
    }
}

int main(int argc, char const *argv[]) {
    tty_mode(0);
    set_cr_noecho_mode();
    int response = get_response(PROMPT_ASK);
    tty_mode(1);

    putchar('\n');
    
    return response;
}
