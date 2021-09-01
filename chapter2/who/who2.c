#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <utmp.h>
#include <time.h>

#define SHOW_HOSTNAME

void show_time(const time_t time_to_show) {
    char *time_str = ctime(&time_to_show);
    // Print time like '2021-Sep-1 18:33'
    printf("%.4s", time_str + 20);
    printf("-");
    printf("%.3s", time_str + 4);
    printf("-");
    printf("%.1s", time_str + 9);
    printf(" ");
    printf("%.5s", time_str + 11);
}

void show_info(struct utmp current_record) {
    // 显示格式为：
    // --------------------------------------------
    // |  用户名  |  终端名  |  登录时间  |  登录地址  |
    // --------------------------------------------
    if (current_record.ut_type != USER_PROCESS) {
        // 识别是否是活动用户（Active users），如果不是，则直接返回
        return;
    }
    printf("%-10s", current_record.ut_user);
    printf("  ");
    printf("%-10s", current_record.ut_line);
    printf("  ");
    // 改变时间的显示方式（Absolute time --> Time string in 'ctime' format）
    const time_t login_time = current_record.ut_tv.tv_sec;
    show_time(login_time);
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
