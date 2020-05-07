#include "chess-handicap.h"

void ipc(char *proc, ipc_handler handler) {
    pid_t pid = 0;
    int fds[4];

    pipe(fds[0]);
    pipe(fds[2]);

    if ((pid = fork()) == 0) {
        dup2(fds[2], STDIN_FILENO);
        dup2(fds[1], STDOUT_FILENO);
        dup2(fds[1], STDERR_FILENO);

        prctl(PR_SET_PDEATHSIG, SIGTERM);

        execl(proc);
        return 1;
    }

    close(fds[2]);
    close(fds[1]);

    handler(fds[0], fds[3]);

    kill(pid, SIGKILL);
    waitpid(pid, NULL, 0);
}