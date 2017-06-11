#ifndef _OPEND_H
#define _OPEND_H

#include "../../common.h"
#include <errno.h>

#define CL_OPEN "open"
#define CS_OPEN "/tmp/opend.socket"

extern int debug;
extern char errmsg[];
extern int oflag;
extern char *pathname;

typedef struct {
  int fd;
  uid_t uid;
} Client;

extern Client *client;
extern int client_size;

int cli_args(int, char **);
int client_add(int, uid_t);
void client_del(int);
void loop(void);
void handle_request2(char *, int, int);

#endif