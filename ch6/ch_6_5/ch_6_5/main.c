//
//  main.c
//  ch_6_5
//
//  Created by Leaf on 2017/5/6.
//  Copyright © 2017年 zhuscat. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(int argc, const char * argv[]) {
    time_t cal;
    struct tm *tmp;
    char buf[64];
    time(&cal);
    tmp = localtime(&cal);
    if (strftime(buf, 64, "%Y年%m月%d日 %A %H时%M分%S秒 %Z", tmp) == 0) {
        printf("buffer length 64 is too small\n");
    } else {
        printf("%s\n", buf);
    }
    return 0;
}
