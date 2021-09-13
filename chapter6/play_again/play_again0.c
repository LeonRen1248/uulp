#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

#define PROMPT_ASK "Do you want another transaction(y/n)?"
#define PROMPT_WRONG_INPUT "Cannot understand input, please try y(Y) or n(N)."

int get_response(const char *prompt) {
    int response = 1;
    while (1) {
        printf("%s", prompt);
        switch ( getchar() ) {
            case 'y':
            case 'Y': return 1;
            case 'n':
            case 'N':
            case EOF: return 0;
            // default: {
            //     printf(PROMPT_WRONG_INPUT);
            // }
        }
    }
}

int main(int argc, char const *argv[]) {
    int response = get_response(PROMPT_ASK);
    
    return response;
}
