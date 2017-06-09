//
//  main.c
//  ch8_8_4
//
//  Created by Leaf on 2017/5/10.
//  Copyright © 2017年 zhuscat. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/types.h>
#include <signal.h>

static volatile sig_atomic_t    sigflag;
/* set nonzero by signal handler */
static sigset_t         newmask, oldmask, zeromask;

static void
sig_usr(int signo)  /* one signal handler for SIGUSR1 and SIGUSR2 */
{
    sigflag = 1;
    return;
}

void
TELL_WAIT()
{
    if (signal(SIGUSR1, sig_usr) == SIG_ERR)
        printf("signal(SIGINT) error");
    if (signal(SIGUSR2, sig_usr) == SIG_ERR)
        printf("signal(SIGQUIT) error");
    
    sigemptyset(&zeromask);
    
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGUSR1);
    sigaddset(&newmask, SIGUSR2);
    /* block SIGUSR1 and SIGUSR2, and save current signal mask */
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
        printf("SIG_BLOCK error");
}

void
TELL_PARENT(pid_t pid)
{
    kill(pid, SIGUSR2);     /* tell parent we're done */
}

void
WAIT_PARENT(void)
{
    while (sigflag == 0)
        sigsuspend(&zeromask);  /* and wait for parent */
    
    sigflag = 0;
    /* reset signal mask to original value */
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
        printf("SIG_SETMASK error");
}
void
TELL_CHILD(pid_t pid)
{
    kill(pid, SIGUSR1);         /* tell child we're done */
}

void
WAIT_CHILD(void)
{
    while (sigflag == 0)
        sigsuspend(&zeromask);  /* and wait for child */
    
    sigflag = 0;
    /* reset signal mask to original value */
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
        printf("SIG_SETMASK error");
}

static void charatatime(char *);

int
main(void)
{
    pid_t pid;
    
    TELL_WAIT();
    
    if ((pid = fork()) < 0) {
        fprintf(stderr, "fork error");
        exit(1);
    } else if (pid == 0) {
        WAIT_PARENT();
        charatatime("output from child\n");
        TELL_PARENT(getpid());
    } else {
        charatatime("output from parent\n");
        TELL_CHILD(pid);
        WAIT_CHILD();
    }
    exit(0);
}

static void
charatatime(char *str)
{
    char *ptr;
    int c;
    
    // set unbuffered
    setbuf(stdout, NULL);
    
    for (ptr = str; (c = *ptr++) != 0; )
        putc(c, stdout);
}
