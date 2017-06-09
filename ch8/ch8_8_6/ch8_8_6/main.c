//
//  main.c
//  ch8_8_6
//
//  Created by Leaf on 2017/5/10.
//  Copyright © 2017年 zhuscat. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef SOLARIS
#define PSCMD "ps -a -o pid,ppid,s,tty,comm"
#else
#define PSCMD "ps -o pid,ppid,state,tty,command"
#endif

int
main(void)
{
    pid_t pid;
    
    if ((pid = fork()) < 0) {
        fprintf(stderr, "fork error");
    } else if (pid == 0) {
        exit(0);
    }
    sleep(4);
    system(PSCMD);
    exit(0);
}
