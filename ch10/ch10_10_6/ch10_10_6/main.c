//
//  main.c
//  ch10_10_6
//
//  Created by Leaf on 2017/5/12.
//  Copyright © 2017年 zhuscat. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>

static volatile sig_atomic_t sigflag;
static sigset_t newmask, oldmask, zeromask;

static void
sig_usr(int signo)
{
    sigflag = 1;
}

void
TELL_WAIT(void)
{
    if (signal(SIGUSR1, sig_usr) == SIG_ERR) {
        printf("signal(SIGUSR1) error\n" );
        exit(1);
    }
    if (signal(SIGUSR2, sig_usr) == SIG_ERR) {
        printf("signal(SIGUSR2) error\n");
        exit(1);
    }
    sigemptyset(&zeromask);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGUSR1);
    sigaddset(&newmask, SIGUSR2);
    
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
        printf("SIG_BLOCK error\n");
        exit(1);
    }
}

void
TELL_PARENT(pid_t pid)
{
    kill(pid, SIGUSR2);
}

void
WAIT_PARENT(void)
{
    while (sigflag == 0)
        sigsuspend(&zeromask);
    sigflag = 0;
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
        printf("SIG_SETMASK error\n");
        exit(1);
    }
}

void
TELL_CHILD(pid_t pid)
{
    kill(pid, SIGUSR1);
}

void
WAIT_CHILD(void)
{
    while (sigflag == 0)
        sigsuspend(&zeromask);
    sigflag = 0;
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
        printf("SIG_SETMASK error\n");
    }
}

// 学了管道之后应该可以使用管道通信

static int count = 0;

int
main(void)
{
    TELL_WAIT();
    int fd;
    FILE *file;
    pid_t pid;
    if ((fd = open("ch10_6", O_CREAT | O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO)) < 0) {
        printf("open error");
        exit(1);
    }
    if ((file = fdopen(fd, "r+")) == NULL) {
        printf("fdopen error");
        exit(1);
    }
    setbuf(file, NULL);
    fprintf(file, "%d\n", count);
    if ((pid = fork()) < 0) {
        printf("fork error");
        exit(1);
    } else if (pid == 0) {
        // in child
        ++count;
        while (1) {
            fprintf(file, "in child\n");
            fprintf(file, "%d\n", count);
            TELL_PARENT(getppid());
            WAIT_PARENT();
            count = count + 2;
        }
    }
    // in parent
    WAIT_CHILD();
    while (1) {
        count = count + 2;
        fprintf(file, "in parent\n");
        fprintf(file, "%d\n", count);
        TELL_CHILD(pid);
        WAIT_CHILD();
    }
}

