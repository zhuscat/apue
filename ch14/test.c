#include <stdio.h>
#include <unistd.h>

int
main(void)
{
    printf("%ld\n", sysconf(_SC_PAGE_SIZE));
}