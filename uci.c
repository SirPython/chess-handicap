#include "chess-handicap.h"

void uci_interface(subproc sub) {
    char *msg = NULL;

    recv(sub, &msg);
    send(sub, "uci\n");
    recv(sub, &msg);
    send(sub, "isready\n");
    recv(sub, &msg);
    send(sub, "ucinewgame\n");
    send(sub, "position startpos\n");
    send(sub, "go\n");

    bool cont = true;
    while(cont) {
        recv(sub, &msg);
        char *line = strtok(msg, "\n");
        while(line != NULL) {
            if(line[0] == 'b') {
                printf("Found: %s\n", line);
                cont = false;
                break;
            }

            line = strtok(NULL, "\n");
        }
    }

    // try this out
    // maybe the engines can predict the odds from the beginning
    // have them play some games and see if the odds line up
    // if they do, then you don't need the engines to play a game to determine the odds
}