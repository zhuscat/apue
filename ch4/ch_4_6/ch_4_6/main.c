#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define BLK_SIZE 1024

int
main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "usage: cp source target\n");
        exit(1);
    }
    char *source = argv[1];
    char *target = argv[2];
    int fd;
    int fd_w;
    ssize_t read_size;
    struct stat buf;
    char readbuf[BLK_SIZE];
    char writebuf[BLK_SIZE];
    char current_pos = 0;
    if ((fd = open(source, O_RDWR, FILE_MODE)) < 0) {
        fprintf(stderr, "open file error\n");
        exit(1);
    }
    if ((fd_w = open(target, O_RDWR | O_CREAT | O_TRUNC, FILE_MODE)) < 0) {
        fprintf(stderr, "open file for write error\n");
        exit(1);
    }
    if (fstat(fd, &buf) == -1) {
        fprintf(stderr, "read stat error\n");
        exit(1);
    }
    // 含有空洞的输出是包含空洞的长度
    while ((read_size = read(fd, readbuf, BLK_SIZE)) != 0) {
        if (read_size == -1) {
            fprintf(stderr, "read error\n");
            exit(1);
        }
        for (int i = 0; i < read_size; i++) {
            if (readbuf[i] != 0) {
                writebuf[current_pos++] = readbuf[i];
            }
        }
        if (write(fd_w, writebuf, current_pos) == -1) {
            fprintf(stderr, "write error\n");
            exit(1);
        }
        // 重置为 0，等待下一次循环
        current_pos = 0;
    }
}
