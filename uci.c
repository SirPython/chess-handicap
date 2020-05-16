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

void uci_load_pos(subproc *uci, game *g) {
    send(uci, "position fen ");
    send(uci, g->fen);
    send(uci, " moves ");
    for(int i = 0; i < g->n_moves; i++ ) {
        send(uci, g->moves[i]);
        send(uci, " ");
    }
    send(uci, "\n");
}

void uci_read_info(subproc *uci, info_block *b) {
    bool done = false;
    while(!done) {
        char *buf;
        recv(uci, &buf);

        char *tok = strtok(buf, " \n");
        while(tok != NULL) {
            if(strcmp(tok, "cp") == 0) {
                b->cp = strtok(NULL, " \n");
            } else
            if(strcmp(tok, "mate") == 0) {
                b->mate = true;
                done = true;
            } else
            if(strcmp(tok, "bestmove")) {
                b->move = strtok(NULL, " \n");
                done = true;
            }

            tok = strtok(NULL, " \n");
        }
    }
}

void game_init(game *g, char *fen) {
    g->fen = fen;
    g->n_moves = 0;
}
void game_play(game *g, char *move) {
    memcpy(g->moves[g->n_moves], move, 5);
    g->n_moves = g->n_moves++;
}