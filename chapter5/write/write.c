#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "There need 2 arguments.\n");
        exit(-1);
    }
    int fd;
    char buf[BUFSIZ];
    if ((fd = open(argv[1], O_WRONLY)) == -1) {
        fprintf(stderr, "Error open file ");
        perror(argv[1]);
        exit(1);
    }
    while ((fgets(buf, BUFSIZ, stdin)) != NULL) {
        if ((write(fd, buf, strlen(buf))) == -1) {
            break;
        }
    }
    close(fd);
    
    return 0;
}
