#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>

#define SHOWHOST

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
    printf("%-8.8s ", utbufb->ut_user);     // Username
    printf("%-8.8s ", utbufb->ut_line);     // Devicename
    printf("%10d ", utbufb->ut_tv.tv_sec);  // Time(sec)
#ifdef SHOWHOST
    printf("%s", utbufb->ut_host);          // Hostname
#endif
    printf("\n");
}