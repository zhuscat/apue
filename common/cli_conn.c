#include "../common.h"
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>

#define CLI_PATH "var/tmp/"
#define CLI_PERM S_IRWXU

int
cli_conn(const char *name)
{
    // int fd, len, err, rval;
    // struct sockaddr_un un, sun;
    // int do_unlink = 0;
    
    return 0;
}
