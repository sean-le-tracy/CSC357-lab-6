#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/resource.h>
#include<sys/types.h>
#include <sys/wait.h>

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
        printf("Please input one argument\n");
        return 1;
    }

    pid_t pid1 = fork();
    if (pid1 < 0) {
        perror("fork failed");
        return 1;
    } else if (pid1 == 0) {
        if (execl("./evens.out", "evens.c", argv[1], NULL) == -1){
        perror("execl failed");
        exit(1);
        }
    }

    pid_t pid2 = fork();
    if (pid2 < 0) {
        perror("fork failed");
        return 1;
    } else if (pid2 == 0) {
        if (execl("./odds.out", "odds.c" argv[1], NULL) == -1){
        perror("execl failed");
        exit(1);
        }
    }

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}