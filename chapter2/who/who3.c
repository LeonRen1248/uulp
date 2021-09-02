#include "utmplib.c"

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
    utmp_open(utmp_filename);
    struct utmp *cur_rec;
    while ((cur_rec = utmp_next()) != NULL) {
        show_info(*cur_rec);
    }
    utmp_close();


    return 0;
}
