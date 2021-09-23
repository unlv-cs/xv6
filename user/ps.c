#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/psinfo.h"

int main(int argc, char *argv[]) {
    struct ps_proc ptable[MAX_PROC];
    struct ps_proc *p;
    int err;

    err = ps(ptable);
    if (err < 0) {
        printf("Error getting ptable");
        exit(1);
    }

    p = &ptable[0];
    printf("Process Status\n");
    printf("name\tpid\tstate\t\tpriority\n");
    printf("=========================================\n");
    while (p != &ptable[MAX_PROC - 1] && p->state != 0) {
        printf("%s\t%d\t", p->name, p->pid);
        switch (p->state) {
            case 1:
                printf("%s    ", "USED");
                break;
            case 2:
                printf("%s", "SLEEPING");
                break;
            case 3:
                printf("%s", "RUNNABLE");
                break;
            case 4:
                printf("%s ", "RUNNING");
                break;
            case 5:
                printf("%s  ", "ZOMBIE");
                break;
        }
        printf("\t%d\n", p->priority);
        p++;
    }
    printf("=========================================\n");
    printf("ps test: OK\n");
    exit(0);
}
