#include "../common.h"
#include <termios.h>

int
main(void)
{
    struct termios term;
    long vdisable;
    // isatty 检测标准输入是否为终端设备
    if (isatty(STDIN_FILENO) == 0) {
        err_quit("standard input is not a terminal device");
    }
    // 获取 _POSIX_VDISABLE 的值
    if ((vdisable = fpathconf(STDIN_FILENO, _PC_VDISABLE)) < 0)
        err_quit("fpathconf error or _POSIX_VDISABLE not in effect");
    // 获取 termios 结构体
    if (tcgetattr(STDIN_FILENO, &term) < 0)
        err_sys("tcgetattr error");
    // 使 INTR 无效
    term.c_cc[VINTR] = vdisable;
    term.c_cc[VEOF] = 2;

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &term) < 0)
        err_sys("tcsetattr error");

    exit(0);
}
