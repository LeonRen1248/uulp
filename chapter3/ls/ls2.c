#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <grp.h>
#include <pwd.h>
#include <string.h>
#include <time.h>

void do_ls(char *dirname);
void dostat(char *filename);
void show_file_info(char *filename, struct stat *info);
void mode_to_letters(int mode, char str[]);
char * uid_to_name(uid_t uid);
char * gid_to_name(gid_t gid);

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
        dostat(current_record->d_name);
    }
    closedir(current_dir);
}

void dostat(char *filename) {
    struct stat info;
    if (stat(filename, &info) == -1) {
        perror(filename);
    }
    else {
        show_file_info(filename, &info);
    }
}

void show_file_info(char *filename, struct stat *info) {
    char mode_str[10];
    mode_to_letters(info->st_mode, mode_str);
    printf("%s ", mode_str);
    printf("%3ld ", info->st_nlink);
    printf("%6s ", uid_to_name(info->st_uid));
    printf("%6s ", gid_to_name(info->st_gid));
    printf("%10ld ", info->st_size);
    char *curr_time = ctime(&info->st_mtim.tv_sec);
    curr_time[strlen(curr_time) - 1] = '\0';
    printf("%s ", curr_time);
    printf("%s", filename);
    printf("\n");
}

void mode_to_letters(int mode, char str[]) {
    strcpy(str, "----------");
    if (S_ISDIR(mode)) str[0] = 'd'; // Directory
    if (S_ISCHR(mode)) str[0] = 'c'; // Char devices
    if (S_ISBLK(mode)) str[0] = 'b'; // Block device

    // 3 bits for user
    if (mode & S_IRUSR) str[1] = 'r';
    if (mode & S_IWUSR) str[2] = 'w';
    if (mode & S_IXUSR) str[3] = 'x';

    // 3 bits for group
    if (mode & S_IRGRP) str[4] = 'r';
    if (mode & S_IWGRP) str[5] = 'w';
    if (mode & S_IXGRP) str[6] = 'x';

    // 3 bits for other
    if (mode & S_IROTH) str[7] = 'r';
    if (mode & S_IWOTH) str[8] = 'w';
    if (mode & S_IXGRP) str[9] = 'x';
}

char * uid_to_name(uid_t uid) {
    struct passwd *pw_ptr;
    static char numstr[10];
    if ((pw_ptr = getpwuid(uid)) == NULL) {
        sprintf(numstr, "%d", uid);
    }
    else {
        return pw_ptr->pw_name;
    }
}

char * gid_to_name(gid_t gid) {
    struct group *gp_ptr;
    static char numstr[10];
    if ((gp_ptr = getgrgid(gid)) == NULL) {
        sprintf(numstr, "%d", gid);
        return numstr;
    }
    else {
        return gp_ptr->gr_name;
    }
}