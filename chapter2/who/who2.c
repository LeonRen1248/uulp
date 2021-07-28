#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#define SHOWHOST

void show_info(struct utmp *utbufb);

int main() {
    struct utmp current_record;
    int utmpfd;
    int reclen = sizeof(current_record);

    if ((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1) {
        perror(UTMP_FILE);
        exit(1);
    }
    while (read(utmpfd, &current_record, reclen) == reclen) {
        show_info(&current_record);
    }
    close(utmpfd);

    return 0;
}

void show_info(struct utmp *utbufb) {
    if (utbufb->ut_type != USER_PROCESS)    // Only maintain normal users
        return;
    printf("%-8.8s  ", utbufb->ut_user);     // Username
    printf("%-8.8s  ", utbufb->ut_line);     // Devicename
    long t = utbufb->ut_tv.tv_sec;
    char *time_str = ctime(&t);
    time_str[strlen(time_str) - 1] = '\0';
    printf("%s  ", time_str);  // Time(sec)
#ifdef SHOWHOST
    printf("%s", utbufb->ut_host);          // Hostname
#endif
    printf("\n");
}