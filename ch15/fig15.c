#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAXLINE 4096

int
main(void)
{
    char line[MAXLINE];
    FILE *fpin;
    if ((fpin = popen("./myuclc", "r")) == NULL) {
        printf("popen error\n");
        exit(1);
    }
    for ( ; ; ) {
        // 子进程(myuclc)的标准输出到管道
        fputs("prompt> ", stdout);
        fflush(stdout);
        if (fgets(line, MAXLINE, fpin) == NULL)
            break;
        if (fputs(line, stdout) == EOF) {
            printf("fputs error to pipe\n");
            exit(1);
        }
    }
    if (pclose(fpin) == -1) {
        printf("pclose error\n");
        exit(1);
    }
    putchar('\n');
    exit(0);
}