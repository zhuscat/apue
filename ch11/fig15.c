#include <pthread.h>
#include "../common.h"

struct msg {
    struct msg *m_next;
};

struct msg *workq;

pthread_cond_t qready = PTHREAD_COND_INITIALIZER;

pthread_mutex_t qlock = PTHREAD_MUTEX_INITIALIZER;

void
process_msg(void)
{
    struct msg *mp;

    for (;;) {
        pthread_mutex_lock(&qlock);
        while (workq == NULL)
            pthread_cond_wait(&qready, &qlock);
        mp = workq;
        workq = mp->m_next;
        printf("process one msg\n");
        free(mp);
        pthread_mutex_unlock(&qlock);
    }
}

void
enqueue_msg(struct msg *mp)
{
    pthread_mutex_lock(&qlock);
    mp->m_next = workq;
    workq = mp;
    pthread_mutex_unlock(&qlock);
    pthread_cond_signal(&qready);
}

void *
thr_fn1(void *arg)
{
    process_msg();
    return((void *)0);
}

void *
thr_fn2(void *arg)
{
    struct msg *msg1 = malloc(sizeof(struct msg));
    enqueue_msg(msg1);
    return((void *)0);
}

void *
thr_fn3(void *arg)
{
    printf("thr_fn3 start\n");
    pthread_mutex_lock(&qlock);
    printf("continual wait! thr_fn1, I will print!!!\n");
    pthread_mutex_unlock(&qlock);
    return ((void *)0);
}

int
main(void)
{
    struct msg msg1;
    pthread_t tid1, tid2, tid3, tid4, tid5, tid6, tid7, tid8;
    pthread_create(&tid1, NULL, thr_fn1, NULL);
    pthread_create(&tid2, NULL, thr_fn1, NULL);
    pthread_create(&tid3, NULL, thr_fn1, NULL);
    pthread_create(&tid4, NULL, thr_fn1, NULL);
    pthread_create(&tid5, NULL, thr_fn1, NULL);
    pthread_create(&tid8, NULL, thr_fn3, NULL);
    sleep(2);
    pthread_create(&tid6, NULL, thr_fn2, NULL);
    sleep(1);
    pthread_create(&tid7, NULL, thr_fn2, NULL);
    sleep(10);
}