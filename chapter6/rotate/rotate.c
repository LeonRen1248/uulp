#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// 在尝试这个程序的时候，在命令行中执行一下 stty -echo -icanon 会有更好的体验

int main(int argc, char const *argv[]) {
    char c;
    while ((c = getchar()) != EOF) {
        if (c == 'z') {
            c = 'a';
        }
        else if (islower(c)) {
            c++;
        }
        putchar(c);
    }
    
    return 0;
}
