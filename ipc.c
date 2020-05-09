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

        execl(proc, proc);

        exit(1);
    }
    close(fds[2]);
    close(fds[1]);

    subproc sub;
    sub.in = fds[0];
    sub.out = fds[3];
    handler(sub);

    kill(pid, SIGKILL);
    waitpid(pid, NULL, 0);
}

void comm(subproc sub, char *send, char **recv) {
    write(sub.out, send, strlen(send));

    if(*recv != NULL) {
        free(*recv);
        *recv = NULL;
    }

    char buf[BUF_SIZE];
    size_t n_read, total_read = 0;
    do {
        n_read = read(sub.in, &buf, BUF_SIZE);

        *recv = realloc(*recv, total_read + n_read);
        memcpy(*recv + total_read, buf, n_read);

        total_read += n_read;
    } while(n_read == BUF_SIZE);

    *recv = realloc(*recv, total_read + 1);
    (*recv)[total_read] = '\0';
}