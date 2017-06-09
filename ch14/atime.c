#include "../common.h"
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

int
main(int argc, char *argv[])
{
    if (argc != 2)
        err_quit("usage: atime <filename>");
    int fd;
    struct stat sbuf;
    if ((fd = open(argv[1], O_RDWR)) < 0)
        err_quit("open error");
    if (stat(argv[1], &sbuf) < 0)
        err_quit("fstat error");
    time_t atime = sbuf.st_atime;
    struct tm *lt = localtime(&atime);
    printf("access time: %d:%d:%d\n", lt->tm_hour, lt->tm_min, lt->tm_sec);
    exit(0);
}