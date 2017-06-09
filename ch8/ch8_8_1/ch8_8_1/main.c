//
//  main.c
//  ch8_8_1
//
//  Created by Leaf on 2017/5/9.
//  Copyright © 2017年 zhuscat. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int globvar = 6;

int
main(void)
{
    int var;
    pid_t pid;
    
    var = 88;
    printf("before vfork\n");
    if ((pid = vfork()) < 0) {
        fprintf(stderr, "vfork error");
        exit(1);
    } else if (pid == 0) {
        // in child
        globvar++;
        var++;
        fclose(stdout);
        exit(0);
    }
    printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar, var);
    exit(0);
}
