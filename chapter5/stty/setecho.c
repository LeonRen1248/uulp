#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <string.h>

#define oops(s, x) do {\
    perror(s);\
    exit(x);\
} while (0)

#define error_str(s, x) do {\
    fprintf(stderr, s);\
    exit(x);\
} while(0)

int main(int argc, char const *argv[]) {
    if (argc == 1) {
        error_str("There need more arguments.\n", 1);
    }

    struct termios info;

    if (tcgetattr(0, &info) == -1) {
        oops("tcgetattr", 1);
    }

    if (!strcmp(argv[1], "ON")) {
        info.c_lflag |= ECHO;
    }
    else if (!strcmp(argv[1], "OFF")) {
        info.c_lflag &= (~ECHO);
    }
    else {
        error_str("Invalid options of the 2-nd argument.\n", 1);
    }

    if (tcsetattr(0, TCSANOW, &info) == -1) {
        oops("tcsetattr", 1);
    }
    
    return 0;
}
