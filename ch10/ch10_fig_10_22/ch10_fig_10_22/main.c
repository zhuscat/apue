//
//  main.c
//  ch10_fig_10_22
//
//  Created by Leaf on 2017/5/12.
//  Copyright © 2017年 zhuscat. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

void pr_mask(const char *str)
{
    sigset_t sigset;
    int errno_save;
    
    errno_save = errno;
    if (sigprocmask(0, NULL, &sigset) < 0) {
        fprintf(stderr, "sigprocmask error\n");
    } else {
        printf("%s", str);
        if (sigismember(&sigset, SIGINT))
            printf(" SIGINT");
        if (sigismember(&sigset, SIGQUIT))
            printf(" SIGQUIT");
        if (sigismember(&sigset, SIGUSR1))
            printf(" SIGUSR1");
        if (sigismember(&sigset, SIGALRM))
            printf(" SIGALRM");
        
        printf("\n");
    }
    
    errno = errno_save;
}

static void sig_int(int);

int
main(void)
{
    sigset_t newmask, oldmask, waitmask;
    
    pr_mask("program start: ");
    
    if (signal(SIGINT, sig_int) == SIG_ERR) {
        fprintf(stderr, "signal(SIGINT) error\n");
        exit(1);
    }
    sigemptyset(&waitmask);
    sigaddset(&waitmask, SIGUSR1);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGINT);
    
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
        fprintf(stderr, "SIG_BLOCK error\n");
        exit(1);
    }
    
    pr_mask("in critical region: ");
    
    if (sigsuspend(&waitmask) != -1) {
        fprintf(stderr, "sigsuspend error\n");
        exit(1);
    }
    
    pr_mask("after return from sigsuspend: ");
    
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
        fprintf(stderr, "SIG_SETMASK error\n");
        exit(1);
    }
    
    pr_mask("program exit: ");
    
    exit(0);
}

static void
sig_int(int signo)
{
    pr_mask("\nin sig_int: ");
}
