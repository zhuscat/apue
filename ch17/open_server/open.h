#ifndef _OPEN_H
#define _OPEN_H

#include "../../common.h"
#include <errno.h>

#define CL_OPEN "open"
#define CS_OPEN "/tmp/opend.socket"

int csopen(char *, int);

#endif
