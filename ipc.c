#include "chess-handicap.h"

void ipc(char *proc, ipc_handler handler) {
    int fds[4];
    pipe(&fds[0]);
    pipe(&fds[2]);

    pid_t pid = fork();
    if (pid == 0) {
        dup2(fds[2], STDIN_FILENO);
        dup2(fds[1], STDOUT_FILENO);
        dup2(fds[1], STDERR_FILENO);

        execl(proc, NULL);

        exit(1);
    }

    close(fds[2]);
    close(fds[1]);

    handler(fds[0], fds[3]);

    puts("TERMINATING");
    kill(pid, SIGKILL);
    waitpid(pid, NULL, 0);
}