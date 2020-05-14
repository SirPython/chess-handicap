#include "chess-handicap.h"

void uci_interface(subproc sub) {
    char *msg = NULL;

    send(sub, "");
    recv(sub, &msg);
    send(sub, "uci\n");
    recv(sub, &msg);
    send(sub, "isready\n");
    recv(sub, &msg);
    send(sub, "ucinewgame\n");
    send(sub, "position startpos\n");
    send(sub, "go\n");

    while(true) {
        recv(sub, &msg);
        if(msg[0] != 'b') {
            continue;
        }

        printf("Result: %s\n", msg);
        break;
    }

    // try this out
    // maybe the engines can predict the odds from the beginning
    // have them play some games and see if the odds line up
    // if they do, then you don't need the engines to play a game to determine the odds
}