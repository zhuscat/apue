#include "../common.h"
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include <pwd.h>

int
main(void)
{
    for (int i = 0; i <= 5; i++) {
        int qid;
        if ((qid = msgget(IPC_PRIVATE, 0)) < 0) {
            err_quit("msgget error");
        }
        printf("%d\n", qid);
        struct mymsg msg;
        msg.mtype = 6;
        msg.mtext[0] = 'a';
        if (msgsnd(qid, (void *)&msg, sizeof(struct mymsg), 0) < 0) {
            err_quit("msgsnd error");
        }
    }
}
