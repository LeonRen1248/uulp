#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void f(int signum) {
    printf("OUTH!\n");
}

int main(int argc, char const *argv[]) {
    signal(SIGINT, f);
    for (int i = 0; i < 5; i++) {
        printf("Hello\n");
        sleep(1);
    }
    
    return 0;
}
