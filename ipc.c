#include "chess-handicap.h"

void load_ipc(char *proc, subproc *sub) {
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

    sub->in  = fds[0];
    sub->out = fds[3];
    sub->pid = pid;
}

void kill_ipc(subproc sub) {
    kill(sub.pid, SIGKILL);
    waitpid(sub.pid, NULL, 0);
}

void send(subproc sub, char *msg) {
    write(sub.out, msg, strlen(msg));
}

void recv(subproc sub, char **msg) {
    if(*msg != NULL) {
        free(*msg);
        *msg = NULL;
    }

    char buf[BUF_SIZE];
    size_t n_read, total_read = 0;
    do {
        n_read = read(sub.in, &buf, BUF_SIZE);

        *msg = realloc(*msg, total_read + n_read);
        memcpy(*msg + total_read, buf, n_read);

        total_read += n_read;
    } while(n_read == BUF_SIZE);

    *msg = realloc(*msg, total_read + 1);
    (*msg)[total_read] = '\0';
}