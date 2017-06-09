//
//  main.c
//  ch8_8_2
//
//  Created by Leaf on 2017/5/9.
//  Copyright © 2017年 zhuscat. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void testfunc() {
    pid_t pid;
    if ((pid = vfork()) < 0) {
        fprintf(stderr, "vfork error\n");
        exit(1);
    } else if (pid == 0) {
        printf("in child, ready to return\n");
        return;
    } else {
        printf("in parent, ready to do something\n");
        printf("gonna print\n");
        printf("-----------\n");
    }
}

int
main(void)
{
    printf("before call the func\n");
    testfunc();
    printf("after call the func\n");
    return 0;
}
