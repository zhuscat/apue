#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <errno.h>
#include <syslog.h>
#include <sys/socket.h>

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 256
#endif

int
main(int argc, char *argv[])
{
    int n;
    char *host;
    if ((n = sysconf(_SC_HOST_NAME_MAX)) < 0)
        n = HOST_NAME_MAX;
    if ((host = malloc(n)) == NULL) {
        printf("malloc error\n");
        exit(1);
    }
    if ((gethostname(host, n)) < 0) {
        printf("gethostname error\n");
        exit(1);
    }
    printf("%s\n", host);
    return 0;
}