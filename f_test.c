#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/resource.h>
#include<sys/types.h>
#include<sys/wait.h>


void limit_fork(rlim_t max_procs)
{
struct rlimit rl;
if (getrlimit(RLIMIT_NPROC, &rl))
{
perror("getrlimit");
exit(-1);
}
rl.rlim_cur = max_procs;
if (setrlimit(RLIMIT_NPROC, &rl))
{
perror("setrlimit");
exit(-1);
}
}
int main(int argc, char *argv[]) {
if (argc != 2) { 
    printf("please enter a single integer\n");
    return 1;
}

limit_fork(50);

pid_t pid = fork();

    char *ptr;
    long val = strtol(argv[1], &ptr, 12);

    if (*ptr != '\0') {
        printf("please enter an integer\n");
        return 1;
    }

    if (val < 1) {
        printf("please enter a non-zero positive integer\n");
        return 1;
    }

    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        for (int i = 1; i <= val; i += 2) {
            printf("%d\n", i);
        }
        exit(0);
    } else {
        for (int i = 2; i <= val; i += 2) {
            printf("\t%d\n", i);
        }
        wait(NULL);
    }
return 0;
}