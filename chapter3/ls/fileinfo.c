#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

void show_stat_info(const char *filename, struct stat fileinfo) {
    printf("%10s: %o\n", "mode", fileinfo.st_mode);
    printf("%10s: %ld\n", "links", fileinfo.st_nlink);
    printf("%10s: %d\n", "user", fileinfo.st_uid);
    printf("%10s: %d\n", "group", fileinfo.st_gid);
    printf("%10s: %ld\n", "size", fileinfo.st_size);
    char *time_str = ctime(&(fileinfo.st_mtim.tv_sec));
    time_str[24] = '\0';
    printf("%10s: %s\n", "modtime", time_str);
    printf("%10s: %s\n", "name", filename);
}

int main(int argc, char const *argv[]) {
    if (argc == 1) {
        fprintf(stderr, "Error: Tow few arguments.\n");
        exit(1);
    }
    struct stat fileinfo;
    while (--argc) {
        int stat_ret = -1;
        if ((stat_ret = stat(*(++argv), &fileinfo)) == -1) {
            fprintf(stderr, "Error: Error get stat info of file: %s\n", *argv);
            exit(1);
        }
        show_stat_info(*argv, fileinfo);
    }
    
    return 0;
}
