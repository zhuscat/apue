//
//  main.c
//  ch10_10_1
//
//  Created by Leaf on 2017/5/12.
//  Copyright © 2017年 zhuscat. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static void sig_usr(int);

int
main(void)
{
    if (signal(SIGUSR1, sig_usr) == SIG_ERR) {
        printf("can't catch SIGUSR1");
        exit(1);
    }
    if (signal(SIGUSR2, sig_usr) == SIG_ERR) {
        printf("can't catch SIGUSR2");
        exit(1);
    }
    pause();
}

static void
sig_usr(int signo)
{
    if (signo == SIGUSR1)
        printf("received SIGUSR1\n");
    else if (signo == SIGUSR2)
        printf("received SIGUSR2\n");
    else {
        printf("received signal %d\n", signo);
        exit(1);
    }
}
