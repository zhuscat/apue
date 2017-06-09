//
//  main.c
//  ch_8_fig_6
//
//  Created by Leaf on 2017/5/8.
//  Copyright © 2017年 zhuscat. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int
main(void)
{
    pid_t pid;
    
    if ((pid = fork()) < 0) {
        fprintf(stderr, "fork error");
        exit(1);
    } else if (pid == 0) {
        if ((pid = fork()) < 0) {
            fprintf(stderr, "fork error");
            exit(1);
        } else if (pid > 0) {
            // parent of the second fork
            exit(0);
        }
        
        // second child, parent is init
        sleep(2);
        printf("second child, parent pid = %ld\n", (long)getpid());
        exit(0);
    }
    
    // here is the first parent
    if (waitpid(pid, NULL, 0) != pid) {
        fprintf(stderr, "waitpid error\n");
    }
    
    exit(0);
}
