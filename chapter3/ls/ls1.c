#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

void do_ls(const char *path) {
    DIR *dirp = NULL;
    struct dirent *dirent_ptr;
    if ((dirp = opendir(path)) == NULL) {
        fprintf(stderr, "Error open directory %s.", path);
        return;
    }
    while ((dirent_ptr = readdir(dirp)) != NULL) {
        if (dirent_ptr->d_name[0] != '.') {
            printf("%s\n", dirent_ptr->d_name);
        }
    }
    closedir(dirp);
}

int main(int argc, char const *argv[]) {
    if (argc == 1) {
        do_ls(".");
    }
    else {
        for (int i = 1; i < argc; i++) {
            printf("==================== %s ====================\n", *(++argv));
            do_ls(*argv);
        }
    }
    
    return 0;
}
