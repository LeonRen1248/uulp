#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <utmp.h>

#define SHOW_HOSTNAME

void show_info(struct utmp current_record) {
    // 显示格式为：
    // --------------------------------------------
    // |  用户名  |  终端名  |  登录时间  |  登录地址  |
    // --------------------------------------------
    printf("%-10s", current_record.ut_user);
    printf("  ");
    printf("%-10s", current_record.ut_line);
    printf("  ");
    printf("%d", current_record.ut_tv.tv_sec);
#ifdef SHOW_HOSTNAME
    printf("  ");
    printf("%-16s", current_record.ut_host);
#endif
    printf("\n");
}

int main(int argc, char const *argv[]) {
    const char *utmp_filename = "/var/run/utmp";
    int utmp_fd = 0;
    if ((utmp_fd = open(utmp_filename, O_RDONLY)) < 0) {
        fprintf(stderr, "Error open /var/run/utmp.");
    }
    struct utmp one_user;
    int numread = 0;
    while ((numread = read(utmp_fd, &one_user, sizeof(struct utmp))) > 0) {
        show_info(one_user);
    }

    close(utmp_fd);

    return 0;
}
