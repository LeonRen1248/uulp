#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>

void do_ls(char *dirname);

int main(int argc, char **argv) {
    if (argc == 1) {
        do_ls(".");
    }
    while (--argc) {
        printf("%s:\n", *(++argv));
        do_ls(*argv);
    }
    
    return 0;
}

void do_ls(char *dirname) {
    DIR *current_dir;
    struct dirent *current_record;
    if ((current_dir = opendir(dirname)) == NULL) {
        fprintf(stderr, "ls1: cannot open %s\n", dirname);
    }
    while (current_record = readdir(current_dir)) {
        printf("%s\n", current_record->d_name);
    }
    closedir(current_dir);
}