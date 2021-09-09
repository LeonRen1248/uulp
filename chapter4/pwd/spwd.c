// A simplified version of command 'pwd'

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

ino_t get_inode(const char *pathname) {
    struct stat info;
    if ((stat(pathname, &info)) == -1) {
        fprintf(stderr, "Error get inode of %s.\n", pathname);
        exit(1);
    }
    return info.st_ino;
}

void inode_to_name(ino_t inode_to_find, char *name_buf, int buflen) {
    DIR *dir_ptr = opendir(".");
    if (!dir_ptr) {
        perror(".");
        exit(1);
    }
    struct dirent *dirent_ptr;
    while ((dirent_ptr = readdir(dir_ptr)) != NULL) {
        if (dirent_ptr->d_ino == inode_to_find) {
            strncpy(name_buf, dirent_ptr->d_name, buflen);
            name_buf[buflen - 1] = '\0';
            closedir(dir_ptr);
            return;
        }
    }
__NOT_FOUND_ERROR__:
    // Not found
    fprintf(stderr, "Error: Not found this file in this directory.\n");
    closedir(dir_ptr);
    exit(1);
}

void print_path_to(ino_t this_inode) {
    ino_t my_inode;
    char its_name[BUFSIZ];
    if ((my_inode = get_inode("..")) != this_inode) {
        chdir("..");
        inode_to_name(this_inode, its_name, BUFSIZ);
        print_path_to(my_inode);
        printf("/%s", its_name);
    }
}

int main(int argc, char const *argv[]) {
    ino_t curr_inode = get_inode(".");
    print_path_to(curr_inode);
    printf("\n");
    
    return 0;
}
