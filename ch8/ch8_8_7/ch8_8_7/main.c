//
//  main.c
//  ch8_8_7
//
//  Created by Leaf on 2017/5/10.
//  Copyright © 2017年 zhuscat. All rights reserved.
//

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <fcntl.h>

int
main(void)
{
    DIR *dirp;
    int dir_fd;
    int val;
    
    if ((dirp = opendir("/")) == NULL) {
        fprintf(stderr, "opendir error\n");
        exit(1);
    }
    if ((dir_fd = dirfd(dirp)) == -1) {
        fprintf(stderr, "dirfd error\n");
        exit(1);
    }
    if ((val = fcntl(dir_fd, F_GETFD)) == -1) {
        fprintf(stderr, "fcntl error\n");
        exit(1);
    }
    if (val & FD_CLOEXEC)
        printf("close-on-exec is on\n");
    else
        printf("close-on-exec is off\n");
    
    if ((dir_fd = open("/", O_DIRECTORY)) == -1) {
        fprintf(stderr, "open error\n");
    }
    if ((val = fcntl(dir_fd, F_GETFD)) == -1) {
        fprintf(stderr, "fcntl error\n");
    }
    
    if (val & FD_CLOEXEC)
        printf("close-on-exec is on\n");
    else
        printf("close-on-exec is off\n");
    
    return 0;
}
