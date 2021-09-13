#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <sys/fcntl.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <signal.h>

#define PROMPT_ASK "Do you want another transaction(y/n)? "
#define PROMPT_WRONG_INPUT "Cannot understand last input, please try y(Y) or n(N): "

#define SLEEPTIME 2
#define TRIES 5
// #define BEEP putchar('\a');

int get_ok_char() {
    int c;
    while ((c = getchar()) != EOF && !(strchr("yYnN", c))) { }
    return c;
}

int get_response(int max_tries) {
    int response = 1;
    printf(PROMPT_ASK);
    fflush(stdout);
    while (1) {
        sleep(SLEEPTIME);
        int input = tolower(get_ok_char());
        if (input == 'y') return 1;
        if (input == 'n') return 1;
        if (--max_tries == 0) return 2;
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

void set_nodelay_mode() {
    int termflags;
    termflags = fcntl(0, F_GETFL);
    termflags |= O_NDELAY;
    fcntl(0, F_SETFL, termflags);
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

void ctrl_c_handler() {
    tty_mode(1);
    putchar('\n');
    exit(1);
}

int main(int argc, char const *argv[]) {
    tty_mode(0);
    set_cr_noecho_mode();
    set_nodelay_mode();

    signal(SIGINT, ctrl_c_handler);
    signal(SIGQUIT, SIG_IGN);

    int response = get_response(TRIES);
    tty_mode(1);

    putchar('\n');
    
    return response;
}
