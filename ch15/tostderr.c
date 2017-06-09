#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int
main(void)
{
    write(STDERR_FILENO, "to", 2);
}