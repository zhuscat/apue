#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>

static jmp_buf env_alrm;

static void
sig_alrm(int signo)
{
    longjmp(env_alrm, 1);
}

unsigned int
sleep2(unsigned int seconds)
{
    if (signal(SIGALRM, sig_alrm) == SIG_ERR)
        return(seconds);
    if (setjmp(env_alrm) == 0) {
        alarm(seconds);
        pause();
    }
    return(alarm(0));
}

static void
sig_int(int signo)
{
    int i, j;
    volatile int k;
    printf("\nsig_int starting\n");
    for (i = 0; i < 300000000; i++)
        for (j = 0; j < 400000000; j++)
            k = 1;
    printf("sig_int finished\n");
}

int
main(void)
{
    unsigned int unslept;
    if (signal(SIGINT, sig_int) == SIG_ERR) {
        printf("signal(SIGINT) error\n");
        exit(1);
    }
    unslept = sleep2(2);
    printf("sleep2 returned: %u\n", unslept);
    exit(0);
}