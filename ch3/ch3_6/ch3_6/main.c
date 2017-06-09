#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

char buf[] = "This is a buffer";

int
main(void)
{
    int fd;
    off_t pos;
    char readBuf[1024];
    if ((fd = open("./test.txt", O_RDWR, FILE_MODE)) < 0) {
        printf("open file error\n");
    }
    if (write(fd, buf, 16) != 16) {
        printf("write error\n");
    }
    if ((pos = lseek(fd, 0, SEEK_SET)) == -1) {
        printf("cannot seek\n");
    }
    if (read(fd, readBuf, 1024) > 0) {
        printf("%s\n", readBuf);
    }
//    if ((pos = lseek(fd, 0, SEEK_SET)) == -1) {
//        printf("cannot seek\n");
//    }
//    printf("pos: %lld", pos);
//    if (write(fd, "Added", 5) != 5) {
//        printf("write error\n");
//    }
    exit(0);
}
