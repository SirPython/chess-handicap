#include "chess-handicap.h"

void uci_interface(subproc sub) {
    char *msg = NULL;

    send(sub, "");
    recv(sub, &msg);
    puts(msg);

    send(sub, "uci\n");
    recv(sub, &msg);
    puts(msg);

    send(sub, "isready\n");
    recv(sub, &msg);
    puts(msg);

    send(sub, "ucinewgame\n");
    send(sub, "position startpos moves e2e4\n");
    send(sub, "go wtime 122000 btime 120000 winc 2000 binc 2000\n");
    recv(sub, &msg);
    puts(msg);
    recv(sub, &msg);
    puts(msg);
    recv(sub, &msg);
    puts(msg);
    recv(sub, &msg);
    puts(msg);
    recv(sub, &msg);
    puts(msg);
}