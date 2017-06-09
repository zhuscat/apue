#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int mydup2(int fd, int fd2);

int
main(void)
{
    int fd, fd2;
    if ((fd = open("test.txt", O_RDWR | O_CREAT | O_TRUNC)) == -1) {
        fprintf(stderr, "open error\n");
    }
    if ((fd2 = mydup2(fd, 6)) == -1) {
        fprintf(stderr, "dup2 error\n");
    }
    printf("fd2: %d\n", fd2);
}

int mydup2(int fd, int fd2) {
    long openmax = sysconf(_SC_OPEN_MAX);
    int arr[openmax];
    int current = 0;
    int n;
    if (fd < 0 || fd >= openmax) {
        fprintf(stderr, "invalid fd provided: %d\n", fd);
        exit(1);
    }
    if (fd2 < 0 || fd2 >= openmax) {
        fprintf(stderr, "invalid fd2 provided: %d\n", fd2);
        exit(1);
    }
    // 测试 fd 是否可用
    n = dup(fd);
    if (n == -1) {
        return -1;
    } else {
        close(n);
    }
    if (fd == fd2) {
        return fd2;
    }
    // 先关闭 fd2（不管有没有打开）
    close(fd2);
    while ((n = dup(fd)) < fd2) {
        if (n == -1) {
            return -1;
        }
        arr[current++] = n;
    }
    for (int i = 0; i < current - 1; i++) {
        close(arr[i]);
    }
    return fd2;
}
