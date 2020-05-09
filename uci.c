#include "chess-handicap.h"

void uci_interface(subproc sub) {
    char *msg = NULL;
    comm(sub, "", &msg);

    printf("receieved: %s\n", msg);

    comm(sub, "uci\n", &msg);
    printf("receieved: %s\n", msg);
}