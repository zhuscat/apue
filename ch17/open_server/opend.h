#ifndef _OPEND_H
#define _OPEND_H

#include "../../common.h"
#include <errno.h>

#define CL_OPEN "open"

extern char errmsg[];
extern int oflag;
extern char *pathname;

int cli_args(int, char **);
void handle_request(char *, int, int);

#endif