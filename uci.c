#include "chess-handicap.h"

void uci_interface(int in, int out) {
    char *msg;
    int n = read_msg(in, &msg);

    printf("1Read %d bytes: %s", n, msg);
    free(msg);

    n = read_msg(in, &msg);
    printf("2Read %d bytes: %s", n, msg);
    free(msg);

    char buuf[256] = "uci";
    write(out, buuf, strlen(buuf));
    printf("just wrote");

    n = read_msg(in, &msg);
    printf("3Read %d bytes: %s", n, msg);
    free(msg);
}

int read_msg(int fd, char **msg) {
    /* Don't really matter what you initalize it to. */
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