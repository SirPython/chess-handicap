#include "chess-handicap.h"

void uci_interface(int in, int out) {
    char *msg;
    int n = read_msg(in, &msg);

    printf("Read %d bytes: %s", n, msg);
}

int read_msg(int fd, char **msg) {
    *msg = malloc(BUF_SIZE);

    char buf[BUF_SIZE];
    size_t n_read, total_read = 0;
    do {
        n_read = read(fd, &buf, BUF_SIZE);

        *msg = realloc(*msg, total_read + n_read);
        memcpy(*msg + total_read, buf, n_read);

        total_read += n_read;
    } while(n_read == BUF_SIZE);

    *msg = realloc(*msg, total_read + 1);
    (*msg)[total_read] = '\0';

    return total_read;
}