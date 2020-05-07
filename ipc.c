#include "chess-handicap.h"

void ipc(char *proc, ipc_handler handler) {
    int fds[4];
    pipe(&fds[0]);
    pipe(&fds[2]);

    puts("okay fellas");
    pid_t pid = fork();
    if (pid == 0) { // IS FORK GONNA WORK FUNKY CAUSE THIS IS IN A SUBROUTINE?
        puts("this is the child process because fork() returns 0 for children");
        dup2(fds[2], STDIN_FILENO);
        dup2(fds[1], STDOUT_FILENO);
        dup2(fds[1], STDERR_FILENO);

        execl(proc, NULL); // maybe null works?

        puts("This shouldn't be reached.");
        exit(1);
    }

    puts("this is the parent process because children get caught in execl");

    close(fds[2]);
    close(fds[1]);

    handler(fds[0], fds[3]);

    kill(pid, SIGKILL);
    waitpid(pid, NULL, 0);
}