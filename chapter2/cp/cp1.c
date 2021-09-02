#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#define COPY_MODE 0644
#define BUFFER_SIZE 4096

void oops(int num, ...) {
    // 其实这个函数没必要这样设计，这里纯粹是为了练习一下可变数量参数（...）的用法
    va_list ap;
    va_start(ap, num);
    fprintf(stderr, "Error: ");
    for (int i = 0; i < num - 1; i++) {
        fprintf(stderr, "%s ", va_arg(ap, char *));
    }
    perror(va_arg(ap, char *));
    fprintf(stderr, "\n");
    va_end(ap);
}


int main(int argc, char const *argv[]) {
    char buffer[BUFFER_SIZE];

    if (argc != 3) {
        fprintf(stderr, "This command has incorrect number of arguments.\n");
        exit(1);
    }

    int read_fd = -1, write_fd = -1;
    if ((read_fd = open(argv[1], O_RDONLY)) == -1) {
        oops(2, "Cannot open file", argv[1]);
        goto __ERROR__;
    }
    
    if ((write_fd = creat(argv[2], COPY_MODE)) == -1) {
        oops(2, "Cannot create file ", argv[2]);
        goto __ERROR__;
    }

    int num_read = 0, num_write = 0;
    while ((num_read = read(read_fd, buffer, BUFFER_SIZE)) > 0) {
        if ((num_write = write(write_fd, buffer, num_read) != num_read)) {
            oops(2, "Write error to file ", argv[2]);
        }
    }

__ERROR__:
    if (read_fd != -1) {
        if ((close(read_fd)) == -1) {
            oops(2, "Error close file ", argv[1]);
        }
    }
    if (write_fd != -1) {
        if ((close(write_fd)) == -1) {
            oops(2, "Error close file ", argv[2]);
        }
    }

    return 0;
}
