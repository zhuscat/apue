#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int
makethread(void *(*fn)(void *), void *arg)
{
    int err;
    pthread_t tid;
    pthread_attr_t attr;
    err = pthread_attr_init(&attr);
    if (err != 0) {
        return(err);
    }
    err = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if (err == 0) {
        err = pthread_create(&tid, &attr, fn, arg);
    }
    pthread_attr_destroy(&attr);
    return(err);
}

int
main(void)
{
    #ifdef _POSIX_THREAD_PROCESS_SHARED
    printf("support shared attr\n");
    #else
    printf("not support shared attr\n");
    #endif
    return 0;
}