#include "../common.h"
#include <sys/socket.h>

int
main(void)
{
    int fd;
    struct stat sbuf;
    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        err_quit("socket error");
    }
    if (fstat(fd, &sbuf) < 0) {
        err_quit("fstat error");
    }
}