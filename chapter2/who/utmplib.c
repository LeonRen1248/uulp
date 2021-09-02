#ifndef __UTMPLIB_C__
#define __UTMPLIB_C__


#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <utmp.h>
#include <time.h>

#define NUM_RECORDS 16
#define UTMP_SIZE sizeof(struct utmp)

static char utmpbuf[NUM_RECORDS * UTMP_SIZE];
static int num_recs = 0;
static int cur_recs = 0;
static int utmp_fd = -1;

int utmp_open(const char *filename) {
    utmp_fd = open(filename, O_RDONLY);
    num_recs = 0;
    cur_recs = 0;
    return 0;
}

static int utmp_reload() {
    int num_chars = read(utmp_fd, utmpbuf, NUM_RECORDS * UTMP_SIZE);
    num_recs = num_chars / UTMP_SIZE;
    cur_recs = 0;
    return num_recs;
}

struct utmp *utmp_next() {
    if (utmp_fd == -1) {
        return NULL;
    }
    if ((cur_recs == num_recs) && utmp_reload() == 0) {
        return NULL;
    }
    struct utmp *recp = (struct utmp *)&utmpbuf[cur_recs * UTMP_SIZE];
    ++cur_recs;
    return recp;
}

int utmp_close() {
    if (utmp_fd != -1) {
        close(utmp_fd);
    }
}


#endif