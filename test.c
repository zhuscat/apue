#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <pwd.h>
#include <grp.h>
#include <signal.h>
#include <time.h>
#include <pthread.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <syslog.h>


int
main(void)
{
    int fd = socket(AF_UNIX, SOCK_STREAM, 0);
    // 关闭读
    // shutdown(fd, SHUT_RD);
    // 关闭写
    // shutdown(fd, SHUT_WR);
    // 关闭读写
    // shutdown(fd, SHUT_RDWR);
    // 在网络上传输是使用大端的
    // uint32_t n = htonl(32);
    // printf("%u\n", n);
    // struct sockaddr addr;
    // 需要注意到的是 addr 是网络字节序，也就是说要是大端的
    // int addr = 16885952;
    // char buf[INET_ADDRSTRLEN];
    // inet_ntop(AF_INET, (void *)&addr, buf, INET_ADDRSTRLEN);
    // printf("%s\n", buf);
    // sethostent(1);
    // struct hostent *he = NULL;
    // while ((he = gethostent()) != NULL) {
    //     printf("%s ", he->h_name);
    //     switch (he->h_addrtype) {
    //         case AF_INET:
    //             printf("ipv4\n");
    //             break;
    //         case AF_INET6:
    //             printf("ipv6\n");
    //             break;
    //     }
    // }
    // endhostent();
    // setnetent(1);
    // struct netent *ne = NULL;
    // while ((ne = getnetent()) != NULL) {
    //     printf("%s\n", ne->n_name);
    // }
    // endnetent();
    // setprotoent(1);
    // struct protoent *pe = NULL;
    // while ((pe = getprotoent()) != NULL) {
    //     printf("%s\n", pe->p_name);
    // }
    // endprotoent();
    // setservent(1);
    // struct servent *se = NULL;
    // while ((se = getservent()) != NULL) {
    //     printf("%s %d\n", se->s_name, se->s_port);
    // }
    // endservent();
    struct addrinfo *info_head;
    int err = getaddrinfo("127.0.0.1", "netcp", NULL, &info_head);
    if (err != 0) {
        printf("something error happened %s", gai_strerror(err));
        exit(1);
    }
    printf("%d\n", info_head->ai_protocol);
    // struct msghdr msg;
    // syslog(LOG_ERR, "this is a test");
}
