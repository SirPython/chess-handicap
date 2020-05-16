#include "chess-handicap.h"

void uci_init(subproc *uci) {
    char *_t;

    recv(uci, &_t);
    send(uci, "uci\n");
    recv(uci, &_t);
    send(uci, "isready\n");
    recv(uci, &_t);
    send(uci, "ucinewgame\n");
}

void uci_calc(subproc *uci) {
    send(uci, "go");
}

void uci_load_pos(subproc *uci, char *fen, char **moves, int n_moves) {
    send(uci, "position fen ");
    send(uci, fen);
    send(uci, " moves ");
    for(int i = 0; i < n_moves; i++ ) {
        send(uci, moves[i]);
        send(uci, " ");
    }
    send(uci, "\n");
}

void uci_read_info(subproc *uci, char **info) {
    if(*info != NULL) {
        free(*info);
        *info = NULL;
    }

    bool done = false;
    while(!done) {
        char *buf;
        recv(uci, &buf);

        char *line = strtok(buf, "\n");
        while(line != NULL) {
            if(line[0] == 'b') {
                done = true;
            }
        }

        
    }
}