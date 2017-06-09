#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int
main(void)
{
    printf("%ld", sysconf(_SC_V6_ILP32_OFF32));
    int fd;
    
    if ((fd = creat("file.hole", FILE_MODE)) < 0) {
        printf("creat error");
    }
    
    if (write(fd, buf1, 10) != 10) {
        printf("buf1 write error");
    }
    
    if (lseek(fd, 16384, SEEK_SET) == -1) {
        printf("lseek error");
    }
    
    if (write(fd, buf2, 10) != 10) {
        printf("buf2 write error");
    }
    
    exit(0);
}
