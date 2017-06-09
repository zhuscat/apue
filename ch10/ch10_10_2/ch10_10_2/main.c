//
//  main.c
//  ch10_10_2
//
//  Created by Leaf on 2017/5/12.
//  Copyright © 2017年 zhuscat. All rights reserved.
//

#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int sig2str(int signo, char *str);

int main(int argc, const char * argv[]) {
    // insert code here...
    char str[10];
    sig2str(1, str);
    printf("%s\n", str);
    return 0;
}

int
sig2str(int signo, char *str)
{
    if (signo < 0 || signo > 31) {
        return -1;
    }
    strcpy(str, sys_siglist[signo]);
    return 0;
}
