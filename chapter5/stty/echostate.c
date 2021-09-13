#include <stdio.h>
#include <termios.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
    struct termios info;
    int rv;

    rv = tcgetattr(0, &info);
    if (rv == -1) {
        perror("tcgetattr");
        exit(-1);
    }

    if (info.c_lflag & ECHO) {
        printf("echo is ON, since its bits is 1.\n");
    }
    else {
        printf("echo is OFF, since its bits is 0.\n");
    }
    
    return 0;
}
