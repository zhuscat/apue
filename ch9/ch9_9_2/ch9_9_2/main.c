//
//  main.c
//  ch9_9_2
//
//  Created by Leaf on 2017/5/10.
//  Copyright © 2017年 zhuscat. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int
main(void)
{
    pid_t pid;
    if ((pid = fork()) < 0) {
        fprintf(stderr, "fork error\n");
        exit(1);
    } else if (pid == 0) {
        sleep(2);
        pid_t sid;
        sid = setsid();
        if (sid == -1) {
            fprintf(stderr, "setsid error\n");
            exit(0);
        }
        if (sid == getpid()) {
            printf("child process is the process group leader\n");
        }
    }
    exit(0);
}
