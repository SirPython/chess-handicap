#include "chess-handicap.h"

void uci_interface(subproc sub) {
    /*char *msg = malloc(256);

    comm(io, "uci", &msg);
    int n = read_msg(in, &msg);

    printf("Read %d bytes: %s", n, msg);
    free(msg);

    char buuf[256] = "uci\n";
    write(out, buuf, strlen(buuf));
    printf("just wrote this: %s\n", buuf);

    n = read_msg(in, &msg);

    printf("Read %d bytes: %s", n, msg);
    free(msg);*/

    char *msg;
    comm(sub, "uci", &msg);
}