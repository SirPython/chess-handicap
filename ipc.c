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

    handler(int[] {fds[0], fds[3]});

    puts("TERMINATING");
    kill(pid, SIGKILL);
    waitpid(pid, NULL, 0);
}

int comm(int[2] io, char *send, char **recv) {
    write(io[1], in, strlen(in));

    /* Don't really matter what you initalize it to. */
    free(out);
    *out = malloc(BUF_SIZE);

    char buf[BUF_SIZE];
    size_t n_read, total_read = 0;

    do {
        n_read = read(fd, &buf, BUF_SIZE);

        *out = realloc(*out, total_read + n_read);
        memcpy(*out + total_read, buf, n_read);

        total_read += n_read;
    } while(n_read == BUF_SIZE);

    *out = realloc(*msg, total_read + 1);
    (*out)[total_read] = '\0';

    return total_read;
}