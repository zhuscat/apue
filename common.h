#ifndef _COMMON_H
#define _COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <stdarg.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>
#include <errno.h>
#include <sys/socket.h>
#include <syslog.h>
#include <stddef.h>

#define MAXLINE 4096

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

#ifdef OPEN_MAX
static long openmax = OPEN_MAX;
#else
static long openmax = 0;
#endif

#define OPEN_MAX_GUESS 256


void pr_mask(const char *str);

int set_cloexec(int fd);

void set_fl(int fd, int flags);

void clr_fl(int fd, int flags);

int lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len);

pid_t lock_test(int fd, int type, off_t offset, int whence, off_t len);

#define read_lock(fd, offset, whence, len) \
    lock_reg((fd), F_SETLK, F_RDLCK, (offset), (whence), (len))

#define readw_lock(fd, offset, whence, len) \
    lock_reg((fd), F_SETLKW, F_RDLCK, (offset), (whence), (len))

#define write_lock(fd, offset, whence, len) \
    lock_reg((fd), F_SETLK, F_WRLCK, (offset), (whence), (len))

#define writew_lock(fd, offset, whence, len)\
    lock_reg((fd), F_SETLKW, F_WRLCK, (offset), (whence), (len))

#define un_lock(fd, offset, whence, len)\
    lock_reg((fd), F_SETLK, F_UNLCK, (offset), (whence), (len))

#define is_read_lockable(fd, offset, whence, len)\
    (lock_test((fd), F_RDLCK, (offset), (whence), (len)) == 0)

#define is_write_lockable(fd, offset, whence, len)\
    (lock_test((fd), F_WRLCK, (offset), (whence), (len)) == 0)

static void sig_usr(int signo);

void TELL_WAIT(void);

void TELL_PARENT(pid_t pid);

void WAIT_PARENT(void);

void TELL_CHILD(pid_t pid);

void WAIT_CHILD(void);

/* this function can lock the entire file */
int lockfile(int fd);

ssize_t readn(int fd, void *ptr, size_t n);

ssize_t writen(int fd, const void *ptr, size_t n);

typedef void Sigfunc(int);

Sigfunc *signal_intr(int signo, Sigfunc *func);

long open_max(void);

#define MAXSLEEP 128

/* 进行连接，并在不成功的情况下进行响应的重试 */
int connect_retry(int domain, int type, int protocol,
              const struct sockaddr *addr, socklen_t alen);

/* 初始化一个服务器 */
int initserver(int type, const struct sockaddr *addr, socklen_t alen, int qlen);

/* 对 cmd 进行守护进程化 */
void daemonize(const char *cmd);

int fd_pipe(int fd[2]);

int serv_listen(const char *name);

int serv_accept(int listenfd, uid_t *uidptr);

int cli_conn(const char *name);

int send_fd(int fd, int fd_to_send);

int send_err(int fd, int status, const char *errmsg);

int recv_fd(int fd, ssize_t (*userfunc)(int, const void *, size_t));

#define MAXARGC 50
#define WHITE " \t\n"

int buf_args(char *buf, int (*optfunc)(int, char **));

void err_ret(const char *fmt, ...);

void err_sys(const char *fmt, ...) __attribute__((noreturn));

void err_cont(int error, const char *fmt, ...);

void err_exit(int error, const char *fmt, ...);

void err_dump(const char *fmt, ...) __attribute__((noreturn));

void err_quit(const char *fmt, ...) __attribute__((noreturn));

void log_open(const char *, int, int);
void log_quit(const char *, ...) __attribute__((noreturn));
void log_ret(const char *, ...);
void log_sys(const char *, ...) __attribute__((noreturn));
void log_msg(const char *, ...);
void log_exit(int, const char *, ...) __attribute__((noreturn));

#endif
