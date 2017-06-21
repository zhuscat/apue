#include <stdio.h>
#include <unistd.h>

int
main(void)
{
    printf("%d\n", isatty(STDIN_FILENO));
}
