//
//  main.c
//  ch8_8_3
//
//  Created by Leaf on 2017/5/9.
//  Copyright © 2017年 zhuscat. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void
pr_exit(int status)
{
    if (WIFEXITED(status))
        printf("normal termination, exit status = %d\n",
               WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        printf("abnormal termination, signal number = %d%s\n",
               WTERMSIG(status),
#ifdef WCOREDUMP
               WCOREDUMP(status) ? " (core file generated)" : "");
#else
               "");
#endif
    else if (WIFSTOPPED(status))
        printf("child stopped, signal number = %d\n",
               WSTOPSIG(status));
}

int
main(void)
{
    pid_t pid;
    int status;
    siginfo_t info;
    if ((pid = fork()) < 0) {
        fprintf(stderr, "fork error");
        exit(1);
    } else if (pid == 0) {
        exit(7);
    }
    if ((waitid(P_PID, pid, &info, WEXITED | WCONTINUED | WNOWAIT | WSTOPPED)) == -1) {
        fprintf(stderr, "waitid error");
        exit(1);
    }
    printf("%d\n",   info.si_status);
    
    if ((pid = fork()) < 0) {
        fprintf(stderr, "fork error");
        exit(1);
    } else if (pid == 0) {
        abort();
    }
    
    if ((waitid(P_PID, pid, &info, WEXITED | WCONTINUED | WNOWAIT | WSTOPPED)) == -1) {
        fprintf(stderr, "waitid error");
        exit(1);
    }
    printf("%d\n",   info.si_status);

    
    if ((pid = fork()) < 0) {
        fprintf(stderr, "fork error");
        exit(1);
    } else if (pid == 0)
        status /= 0;
    
    if ((waitid(P_PID, pid, &info, WEXITED | WCONTINUED | WNOWAIT | WSTOPPED)) == -1) {
        fprintf(stderr, "waitid error");
        exit(1);
    }
    printf("%d\n",   info.si_status);
    
    
    exit(0);
}
