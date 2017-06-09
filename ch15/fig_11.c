#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define PAGER "${PAGER:-more}"
#define MAXLINE 4096

int
main(int argc, char *argv[])
{
    char line[MAXLINE];
    FILE *fpin, *fpout;

    if (argc != 2) {
        printf("usage: fig_11.out <pathname>\n");
        exit(1);
    }
    if ((fpin = fopen(argv[1], "r")) == NULL) {
        printf("can't open %s\n", argv[1]);
        exit(1);
    }
    if ((fpout = popen(PAGER, "w")) == NULL) {
        if (fgets(line, MAXLINE, fpin) != NULL) {
            if (fputs(line, fpout) == EOF) {
                // ...
            }
        }
    }
}