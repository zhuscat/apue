#include "../common.h"

int
main(void)
{
    FILE *fp;
    char line[MAXLINE];
    // 这样一来相当于把ls的标准错误和标准输出指向同一个文件描述符了
    if ((fp = popen("./tostderr", "r")) == NULL) {
        err_quit("popen failed");
    } 
    for (;;) {
        if (fgets(line, MAXLINE, fp) == NULL)
            break;
        if (fputs(line, stdout) == EOF)
            err_sys("fputs error to pipe");
    }
    putchar('\n');
    exit(0);
}