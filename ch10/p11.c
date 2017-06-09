#include "../common.h"

#define BUFFSIZE 100

typedef void Sigfunc(int);

Sigfunc *signal_intr(int signo, Sigfunc *func)
{
    struct sigaction act, oact;

    act.sa_handler = func;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
#ifdef SA_INTERRUPT
    act.sa_flags |= SA_INTERRUPT;
#endif
    if (sigaction(signo, &act, &oact) < 0)
        return(SIG_ERR);
    return(oact.sa_handler);
}

static void
sig_xfsz(int signo)
{
    printf("in sig_xfsz\n");
}

int
main(void)
{
    int n;
    char buf[BUFFSIZE];
    int wn;
    struct rlimit rlptr;
    if (getrlimit(RLIMIT_FSIZE, &rlptr) != 0)
        err_sys("getrlimit error");
    rlptr.rlim_cur = 1024;
    if (setrlimit(RLIMIT_FSIZE, &rlptr) != 0)
        err_sys("setrlimit error");
    if (signal_intr(SIGXFSZ, sig_xfsz) == SIG_ERR)
        err_sys("SIGXFSZ error");
    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0) {
        wn = write(STDOUT_FILENO, buf, n);
        printf("%d\n", wn);
        if (wn != n)
            err_sys("write number: %s\n", wn);
    }
    if (n < 0)
        err_sys("read error");
    exit(0);
}