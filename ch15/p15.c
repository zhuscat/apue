#include "../common.h"
#include <fcntl.h>
#include <sys/sem.h>

#define SEM_MODE 0600 /* user read/write */

int
sem_lock_init()
{
    int semid;
    if ((semid = semget(IPC_PRIVATE, 1, IPC_CREAT|SEM_MODE)) < 0) {
        return -1;
    }
    union semun su;
    su.val = 1;
    if (semctl(semid, 0, SETVAL, su) < 0) {
        return -1;
    }
    return semid;
}

int
sem_lock(int lockid)
{
    struct sembuf buf;
    buf.sem_num = 0;
    buf.sem_op = -1;
    buf.sem_flg = 0;
    if (semop(lockid, &buf, 1) < 0) {
        return -1;
    }
    return 0;
}

int sem_unlock(int lockid)
{
    struct sembuf buf;
    buf.sem_num = 0;
    buf.sem_op = 1;
    buf.sem_flg = 0;
    if (semop(lockid, &buf, 1) < 0) {
        return -1;
    }
    return 0;
}

int
sem_lock_destroy(int lockid)
{
    if (semctl(lockid, 0, IPC_RMID, NULL) < 0) {
        return -1;
    }
    return 0;
}

int
main(void)
{
    int lockid;
    int pid;
    if ((lockid = sem_lock_init()) < 0) {
        err_quit("sem_lock_init error");
    }
    if ((pid = fork()) < 0) {
        err_quit("fork error");
    } else if (pid > 0) {
        if (sem_lock(lockid) < 0) {
            err_quit("sem_lock error");
        }
        printf("i got the sem\n");
        if (sem_unlock(lockid) < 0) {
            err_quit("sem_unlock error");
        }
        printf("parent done\n");
    } else {
        if (sem_lock(lockid) < 0) {
            err_quit("child sem_lock error");
        }
        printf("child got the sem\n");
        if (sem_unlock(lockid) < 0) {
            err_quit("child sem_unlock error");
        }
        printf("child done\n");
    }
}