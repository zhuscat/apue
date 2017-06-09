//
//  main.c
//  ch_6_3
//
//  Created by Leaf on 2017/5/6.
//  Copyright © 2017年 zhuscat. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/utsname.h>

int main(int argc, const char * argv[]) {
    // insert code here...
    struct utsname *name = (struct utsname*)malloc(sizeof(struct utsname));
    int status = 0;
    if ((status = uname(name)) == -1) {
        fprintf(stderr, "uname error\n");
        exit(1);
    }
    printf("%s\n", name->sysname);
    printf("%s\n", name->nodename);
    printf("%s\n", name->release);
    printf("%s\n", name->version);
    printf("%s\n", name->machine);
    return 0;
}
