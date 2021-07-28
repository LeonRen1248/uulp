#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <pwd.h>

void show_stat_info(char *filename, struct stat *buf);

int main(int argc, char **argv) {
    struct stat info;
    if (argc > 1) {
        if (stat(argv[1], &info) != -1) {
            show_stat_info(argv[1], &info);
        }
        else {
            perror(argv[1]);
        }
    }
    
    return 0;
}

void show_stat_info(char *filename, struct stat *buf) {
    printf("%10s: %o\n", "mode", buf->st_mode);
    printf("%10s: %ld\n", "links", buf->st_nlink);
    printf("%10s: %d\n", "user", buf->st_uid);
    printf("%10s: %d\n", "group", buf->st_gid);
    printf("%10s: %ld\n", "size", buf->st_size);
    char *curr_time = ctime(&buf->st_mtim.tv_sec);
    curr_time[strlen(curr_time) - 1] = '\0';
    printf("%10s: %s\n", "modtime", curr_time);
    printf("%10s: %s\n", "name", filename);
}